    #include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
    #include <wchar.h> 
    #include <WString.h>
    #include <ESP8266WebServer.h>
    #include <DNSServer.h>
    #include <ESP8266Ping.h>
    #include <ESP8266HTTPClient.h>
    #include <ESP8266HTTPUpdateServer.h>
    
    #include <ArduinoJson.h>
    
    /*#include <Modbus.h>
    #include <ModbusIP_ESP8266.h>
    
    //Modbus Registers Offsets (0-9999)
    const int SENSOR_IREG = 100;

    ModbusIP mb;
    
    long ts; */
    
    #include <EEPROM.h> // Gestion de la mémoire de type eeprom pour la sauvegarde des choix
    
    #define ALARME_EEPROM   0   // Addresse de mémorisations des alarmes
    #define NAME_MODULE     1   //Name of module
    #define ADRESS_SERVER   22  // adress of server php
    #define PORT_SERVER     43  // Port of server
    #define PERIOD          50  // Period to send datas in seconds
    #define MEM_SSID        70
    #define MEM_PASSWORD    170 //
    
    
    #define TEMPERATURE_MAX     60    //Temperature maximum
    #define TEMPERATURE_MIN     62    //Température minimum
    #define TEMPERATURE_OFFSET  64 
    #define HUMIDITE_MAX        66    // Humidity relative maximum
    #define HUMIDITE_MIN        68    // Humidity relative minimum
    #define HUMIDITE_OFFSET     70
    #define LEVEL_MAX           72     // Level of water maximum
    #define LEVEL_MIN           74     // level of water min
    #define LEVEL_OFFSET        76
    #define COUNT_MAX        78    // Number of passages maximum
    #define COUNT_MIN        80    // Number of passages maximum 
    #define COUNT_OFFSET     82
    
    float tIn;      // Variable Température intérieur
    long hIn;      // Variable humidité intérieur
    long qIn;      // Variable de la qualité de l'air intérieur
    float tOut;     // Variable température extérieur
    long hOut;     // Variable humidité extérieur
    float pOut;
    long qOut;     // Variable de la qualité de l'air extérieur
    long venti;    // Valeur de la ventilation actuelle;
    
    float u;  // Tension du réseau électrique en volts
    int iU;
    float uT;  // U total
    
    float i;  // Courant consommée
    int iI;   // index for obtain the average
    float iT;
    
    long p; //Puissance instantanée consommée
    int iP;  // Index for obtain the average between both dispatch
    long pT;
    
    long e;   //Energie totale consommée
    float tsalon;    // Température du salon





    int period;                 // period to sent datas

    int index_sent=0;                           //allow to sent data one by one with PERIOD_SENT bettween each
    #define PERIOD_SENT 100                     //one information every 100 ms;
    unsigned long period_sent=0;                //control the last message
    unsigned long number_of_samples;            //Number of samples between two sender 


    String reception;          // Variable pour la réception sur le port série
    int code;                  // Variable code pour l'échange d'information
// Utilitaires pour la gestion des alarmes

    byte activation_alarmes; // Mot utilisé pour l'activation des alarmes
    byte alarmes_actives;     // Drapeau d'activation des alarmes
    int nbenvois=0;           //nombre d'envoi de mail
    
    #define ALARME_G  0  // Bit d'activation de la surveillance d'alarme
    #define ALARME_T  1  //Bit d' Activation des alarmes de température
    #define ALARME_H  2  // Bit d'activation des alarmes d'humidités
    #define ALARME_L  3   //Bit d'activation des alarmes de niveau d'eau
    #define ALARME_C  4   //Bit d'activation des alarmes de comptage
    
    unsigned long  lastmessage;         // heures d'envoi des derniers relevés
    unsigned long  millisecondes;       // Intervalle des relevés en millisecondes
    int nb_cycle_lost_wifi=0;           // test before reboot when the wifi is lost
    
    #define NB_TRYING_CONNECT 4         
    
    
    
    int t_max; // Seuil de déclenchement de la température maximum
    int t_min;  // seuil de déclenchement de la température minimum
    int t_offset;
    int h_max;     // seuil de l'humidité maximum
    int h_min;     // humidité de l'humidité minimump
    int h_offset;
    int l_max;    //niveau maximum
    int l_min;    //niveau minimum
    int l_offset;
    int c_max;    // seuil du nombre de personnes passées
    int c_min;    // seuil du nombre de personnes passées
    int c_offset; 

/* String for commnunication */

    char          name_module[20];          // name of module
    String        ref_module;               // référence du module
    String        version_module;           // version of module
    char          ip_server[15];            // adress ip of the module
    int unsigned  port_server;              // port of server
    String        local_mac;                // adress mac of the module
    String        local_ip;                 // adress ip of module
    String        gate_way;
    String        date;             
    String        currently_time; 


/*********************************************************
 *  Key of communication between Arduino and ESP8266     *
 *********************************************************/


    #define CODE_COMMAND_INFO                           "$I$"
    #define CODE_COMMAND_READ                           "$R$" 
    #define CODE_COMMAND_WRITE                          "$W$" 

    #define         CODE_TENSION                  10
    #define         CODE_COURANT                  11
    #define         CODE_PUISSANCE                12
    #define         CODE_CONSOMMATION             13
    #define         CODE_TEMPERATURE_OUT          14
    #define         CODE_HUMIDITY_OUT             15
    #define         CODE_PRESSURE                 30
    #define         CODE_TEMPERATURE_IN           16
    #define         CODE_HUMIDITY_IN              17
    #define         CODE_CO2                      18
    #define         CODE_SPEED_FAN                19
    #define         CODE_MODE                     28
    #define         CODE_SET_TEMPERATURE_SUMMER   23
    #define         CODE_SET_TEMPERATURE_WINTER   24
    #define         CODE_SET_HUMIDITY_SUMMER      25
    #define         CODE_SET_HUMIDITY_WINTER      26
    #define         CODE_SET_CO2                  27
    #define         CODE_SET_ALTITUDE             29
    #define         CODE_DATE                     31      // Code de la date actuell
    #define         CODE_HEURE                    32      //Code de l'heure actuelle
    #define         CODE_IP                       33      // Adresse IP de connexion
    #define         CODE_GATE_WAY                 34      // Code pour la passerelle
    #define         CODE_MAC                      35      // Adresse MAC du modul wifi

    ESP8266WebServer server(80); // on instancie un serveur ecoutant sur le port 80
    
    String ssid="";
    String password="";
    int    config_mode=0;
    unsigned long delay_reboot;       // delay during the page of connection is open befor reboot
    #define DELAY_REBOOT 120000 
    
    #include <TimeLib.h>       // Use for take date in internet
    #include <NtpClientLib.h>
    
/* setting to update server */

    const char* update_path = "/firmware";
    const char* update_username = "innogreentech";
    const char* update_password = "innogreentech";
    

    ESP8266HTTPUpdateServer httpUpdater;

  

void setup() {

              /* Mod bus configuration

              mb.config("your_ssid", "your_password");
              mb.addIreg(SENSOR_IREG); */
            
              /* Récupération des données mémorisées:*/
              Serial.begin(115200);
              Serial.setDebugOutput(0);
            
              EEPROM.begin(512);                              // allocations  de 512 adresses Mémoires
            
             
              activation_alarmes=EEPROM.read(ALARME_EEPROM); // lecture du réglage des alarmes
              
              char carac='1';   // Name of module
              int a=0;
              while (!(carac=='\0')&&a<20){carac=char (EEPROM.read(NAME_MODULE+a));reception+= carac; a++;} 
              if (reception=='\0'||a==20){reception=F("InnoGreenTech");}
              int c = reception.length() + 1;                               // longueur de la chaîne de caractéres
              reception.toCharArray(name_module, c); 
             // Serial.println(name_module);        
              
              reception="";    // read memory ip adress server
              carac='1';
              a=0;
              while (!(carac=='\0')&&a<20){carac=char (EEPROM.read(ADRESS_SERVER+a));reception+= carac; a++;}
              if (reception=='\0'||a==20){reception=F("InnoGreenTech");} 
              c = reception.length() + 1;       
              reception.toCharArray(ip_server, c);
              //  Serial.println(ip_server);
              

                

            
              byte mem[2];
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(PORT_SERVER+a);}     // load the port server         
              port_server= mem[0]|mem[1]<<8;
              
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(PERIOD+a);}          // load the time period
              period= mem[0]|mem[1]<<8;
              millisecondes=period*1000;

              
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(TEMPERATURE_MAX+a);}          // Récupération de la température Max
              t_max= mem[0]|mem[1]<<8;                                                
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(TEMPERATURE_MIN+a);}          // Récupération de la température Minimum
              t_min= mem[0]|mem[1]<<8;
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(TEMPERATURE_OFFSET+a);}  
              t_offset= mem[0]|mem[1]<<8;
               
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(HUMIDITE_MAX+a);}             // Récupération de l'hummpidité maximum
              h_max= mem[0]|mem[1]<<8; 
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(HUMIDITE_MIN+a);}             // Récupération de l'hummpidité minimum
              h_min= mem[0]|mem[1]<<8;
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(HUMIDITE_OFFSET+a);}  
              h_offset= mem[0]|mem[1]<<8;
               
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(LEVEL_MAX+a);}               // Récupération du niveau maximum
              l_max= mem[0]|mem[1]<<8; 
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(LEVEL_MIN+a);}               // Récupération du niveau minimum
              l_min= mem[0]|mem[1]<<8;
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(LEVEL_OFFSET+a);}  
              l_offset= mem[0]|mem[1]<<8;


               
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(COUNT_MAX+a);}             // Récupération du seuil du nombre de passage
              c_max= mem[0]|mem[1]<<8;
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(COUNT_OFFSET+a);}  
              c_offset= mem[0]|mem[1]<<8; 

              carac='1';                
              a=0;
              while (!(carac=='\0')&&a<100){carac=char (EEPROM.read(MEM_SSID+a));
              if (!(carac=='\0')){ssid +=carac;} a++;}  //récupération du lien d'information
              if (ssid=='\0'||a>50){ssid=F("");}
            
              carac='1';
              a=0;
              while (!(carac=='\0')&&a<100){carac=char (EEPROM.read(MEM_PASSWORD+a));
              if (!(carac=='\0')){password +=carac;} a++;}  //récupération du lien d'information
              if (password=='\0'||a>50){password=F("");}




           /*Connexion wifi*/
           
           WiFi.mode(WIFI_STA);
           
           c =ssid.length()+1;
           char char_ssid[50];
           ssid.toCharArray(char_ssid, c);

           c =password.length()+1;
           char char_password[50];
           password.toCharArray(char_password, c);

        
           WiFi.begin(char_ssid,char_password);
           
             unsigned long time_out_connection = millis();
              while (WiFi.status() != WL_CONNECTED)
              {
                if (millis() - time_out_connection > 20000)
                {
                  Serial.println F("");
                  Serial.println F ("connection Wifi fail !");
            
                  break;
                }
                delay(100);
                Serial.print('-');
              }
           
           if ( WiFi.status()!= WL_CONNECTED)
        
              {
                Serial.println F ("Open setting gate !");
                WiFi.disconnect();
                WiFi.mode(WIFI_AP); 
                delay(200);
                WiFi.softAP("InnoGreenTech", "innogreentech");
                server.on ( "/index.html", handleRoot );    // go to set up wifi page
                delay(100);
                server.on ("/style.css", cssRoot);     // envoi au fichier de configuration de style
                local_mac = WiFi.macAddress();
                delay(100);
                server.begin();

              
              }

             else

             {
           
              
              /*Read the houre and date on internet */
            
              NTP.begin("pool.ntp.org", 1, true);  //configuration de la récupération de la date,  Serveur+1 heure, Heure été/hivers
              NTP.setInterval(3600);                // Toutes les heures
                      
              /*information of module*/

              local_ip=WiFi.localIP().toString().c_str();              
              local_mac=WiFi.macAddress();//.toString().c_str();
              gate_way=WiFi.gatewayIP().toString().c_str();
              ref_module="Greenhouse";
              version_module="V1";

              Serial.print(F("référence:"));Serial.println(ref_module);
              Serial.print(F("Version:"));Serial.println(version_module);
              Serial.print(F("Adresse IP:"));Serial.println(local_ip);
              Serial.print(F("Adresse MAC:"));Serial.println(local_mac); 
              Serial.println(WiFi.gatewayIP());
              Serial.println(WiFi.dnsIP(1)); 
                          
              /* Configuration du serveur Web */
              
              server.on ( "/index.html", indexRoot );    // Renvoi à la page de index
               delay(100);
              server.on ( "/", indexRoot );    // Renvoi à la page de index
               delay(100);
              server.on ( "/add_module.csv", add_module );    // Page for add or modify  module by php server 
               delay(100);
              server.on ( "/config_probe.htlm", config_probe );    // Page for do a configuration of probes by php server
               delay(100);
              server.on ("/style.css", cssRoot);     // envoi au fichier de configuration de style
               delay(100);
              httpUpdater.setup(&server, update_path, update_username, update_password);

             }
              
              /*listen on the server*/
              
              server.begin();

              
              }


void loop() {

            server.handleClient();
            recep_data();
            send_information();
            if (millis()>lastmessage+millisecondes){send_data();}
  
            }

/************************************************
 * Watch doog
 *********************************************/

    #include <avr/wdt.h>                

 
/************************
 *    EEPROM  ADDRESS   *
 ************************/

    #include <EEPROM.h>
    
    #define MEM_MODE                         0   // adresse sauvegarde set_mode_MEM
    #define MEM_SETTING_SUMMER_TEMPERATURE   4   // adresse sauvegarde consigne température ETE
    #define MEM_SETTING_WINTER_TEMPERATURE   8   // adresse sauvegarde consigne température hivers
    #define MEM_SETTING_SUMMER_HUMIDITY     12   // adresse sauvegarde consigne Humidité ETE
    #define MEM_SETTING_WINTER_HUMIDITY     16   // adresse sauvegarde consigne   Humidité Hive
    #define MEM_SETTING_CO2                 20   // Adresse sauvegarde consigne  qualité de l'aire
    #define MEM_SETTING_ALTITUDE            24   // Altitude memory



/*******************************
 *     Set modul radio         *
 *******************************/


    #include <nRF24L01.h>
    #include <printf.h>
    #include <RF24.h>
    #include <RF24_config.h>
    #define CERF 10             // Définition de la pin Enable
    #define CSRF 9              // Définition de la pin Sélection,
    RF24 radio(CERF,CSRF);      // Entrée des informations dans la librairie
    
    byte trans[5];              // Tableau pour la trans mission de données
    long donnee;                // Valeur de la donnée transmise
    byte nature;                // lecture de la nature de la demande de la carte mére




/*********************************************************************
 *                          setting sensor                           *
 *********************************************************************/
    
    #include <DHT.h>
    #include <DHT_U.h>
    #define DHT_IN_PIN  A3 // Branchement des données sur le port A3
    
    #define DHTTYPE DHT22 // Type de capteur (DHT 22 Pour capteurDHT 22)

    
    DHT dht_in(A3,DHTTYPE); //Définition de la sonde intérieur
    
    float tIn=99; // Variable Température intérieur
    long  hIn=99; // Variable humidité intérieur
    long  qIn=400;

    #include "SparkFunBME280.h"
    #include "Wire.h"            
    #include "SPI.h"
    
    BME280  bme_out;
    
    float tOut=99; //Variable température extérieure
    long  hOut=99; // Variable humidité extérieure
    long  pOut=10000; // 

    long venti=1; //Valeur la ventilation actuelle( 0= Arrêt; 1;2;3)
    long vt; // vitesse théorique demandée pour la régulation de  température (de 0 à  3)
    long vh; // vitesse  théorique pour la régulation de l'humidité
    long vq; // vitesse théorique pour la régulation de la qualité de lair

    byte commande; // lecture de la nature de la demande de la carte Vset_mode

    float set_temperature_summer; // consigne de température
    float set_temperature_winter; // consigne de température
    long  set_humidity_summer; // consigne d'humidité été
    long  set_humidity_winter; // consigne d'humidité hiver
    long  set_co2;// consigne de qualité d'air
    long  set_mode;//mode de fonctionnement
    long  set_altitude;
    long  consigne; //Lecture de la mesure
    unsigned long aquisition=0; // variable pour faire une aquisition toute les 2 secondes

    
   #define R1 5 // Relay vitesse 1
   #define R2 6 // Relay vitesse 2
   #define R3 7 // Relay vitesse 3
    

/*********************************************************
 *  Key of communication between Arduino                 *
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
    #define         CODE_SET_ZERO_CO2             27
    #define         CODE_SET_CO2                  20
    #define         CODE_SET_ALTITUDE             29
    #define         CODE_DATE                     31      // Code de la date actuell
    #define         CODE_HEURE                    32      //Code de l'heure actuelle
    #define         CODE_IP                       33      // Adresse IP de connexion
    #define         CODE_GATE_WAY                 34      // Code pour la passerelle
    #define         CODE_MAC                      35      // Adresse MAC du modul wifi
    



void setup() {

/******************************************
 *                Output setting          *
 *****************************************/

  pinMode(R1,OUTPUT);               // relais vitesse 1
  digitalWrite(R1,LOW);
  pinMode(R2,OUTPUT);               // relais vitesse 2
  digitalWrite(R2,LOW);
  pinMode(R3,OUTPUT);               // relais vitesse 3
  digitalWrite(R3,LOW);
 
  Serial.begin(9600); //configuration pour le port série (console)

/*******************************************
 *              probe setting              *
 * *****************************************/

  dht_in.begin(); // Mise en servic de la sonde de température et humidité intérieur

//lecture des données en mémoire, permet un fonctionnement autonome

    byte mem[4];
    long rsave;
    
    for (int a=0;a<4;a++){mem[a]= EEPROM.read (MEM_MODE +a);}// set_mode_MEM de fonctionnement
    set_mode=(long)mem[0]|(long)mem[1]<<8|(long)mem[2]<<16|(long)mem[3]<<24;
    
    
    for (int a=0;a<4;a++){mem[a]= EEPROM.read (MEM_SETTING_SUMMER_TEMPERATURE+a);}// Consigne température d'été
    rsave=(long)mem[0]|(long)mem[1]<<8|(long)mem[2]<<16|(long)mem[3]<<24;
    set_temperature_summer= float(rsave)/100;
    if (set_temperature_summer>99||set_temperature_summer<-99){set_temperature_summer=99;}
    
    
    for (int a=0;a<4;a++){mem[a]= EEPROM.read (MEM_SETTING_WINTER_TEMPERATURE+a);}// Consigne température d'hiver
    rsave=(long)mem[0]|(long)mem[1]<<8|(long)mem[2]<<16|(long)mem[3]<<24;
    set_temperature_winter= float(rsave)/100;
    if (set_temperature_winter>99||set_temperature_winter<-99){set_temperature_winter=99;}
    
    for (int a=0;a<4;a++){mem[a]= EEPROM.read (MEM_SETTING_SUMMER_HUMIDITY+a);}// Consigne humidité d'été
    set_humidity_summer=(long)mem[0]|(long)mem[1]<<8|(long)mem[2]<<16|(long)mem[3]<<24;
    if (set_humidity_summer>99||set_humidity_summer<-99){set_humidity_summer=99;}
    
    for (int a=0;a<4;a++) {mem[a]= EEPROM.read (MEM_SETTING_WINTER_HUMIDITY +a);}// Consigne humidité d'hiver
    set_humidity_winter=(long)mem[0]|(long)mem[1]<<8|(long)mem[2]<<16|(long)mem[3]<<24;
    if (set_humidity_winter>99||set_humidity_winter<-99){set_humidity_winter=99;}
    
    for (int a=0;a<4;a++) {mem[a]= EEPROM.read (MEM_SETTING_CO2 +a);}// Consigne qualité
    set_co2=(long)mem[0]|(long)mem[1]<<8|(long)mem[2]<<16|(long)mem[3]<<24;
    if (set_co2>10000||set_co2<0){set_co2=1000;}

    for (int a=0;a<4;a++) {mem[a]= EEPROM.read (MEM_SETTING_ALTITUDE +a);}// Consigne qualité
    set_altitude=(long)mem[0]|(long)mem[1]<<8|(long)mem[2]<<16|(long)mem[3]<<24;
    if (set_altitude>10000||set_altitude<0){set_altitude=1000;}


    /* Setting radion */

    radio.begin(); //Allumage radio
    radio.enableDynamicPayloads();
    radio.disableDynamicPayloads();
    radio.setRetries(5,5); // délais (Nbx250 usec Nombre de tentatives d'envoi message
    radio.setChannel(90);//canal de diffusion
    radio.setPayloadSize(5); //taille des messages de3 Bytes 1 pour information 2 pour Int
    radio.setPALevel(RF24_PA_HIGH); // niveau d'emission
    radio.setDataRate(RF24_250KBPS);// vitesse de transmission
    radio.openWritingPipe((byte*)"1node");// Ecrit depuis l'adresse de ventillation
    radio.openReadingPipe(1,(byte*)"Cent1");// Adresse de la centrale
    radio.setAutoAck(false);   // Désactivation de l'accusé de réception
    radio.enableDynamicAck();  // Déasactivation de l'accusé de réception
    //attachInterrupt(2,recep,LOW); // Activation des interruptions pour la réception des messages sur pin 21
    //radio.maskIRQ(1,1,0);   // N'accepte que les interruptions de lecture
    radio.startListening(); // Mise en écoute du module radio



/* Start  watch doog */

  wdt_reset();
  bitClear(MCUSR, WDRF);            // Reset du chien de garde
  WDTCSR = (1 << WDCE) | (1 << WDE);   //  Demande de réglage du chien de garde
  WDTCSR =(1<<WDIE)| (1 << WDE)| (0<<WDIF) | (1 << WDP3) | (0 << WDP2)| (0 << WDP1)| (1<< WDP0) ; // Activation Delay 1 seconde 
  
 

/*Set and start BME280 sensor, sensor out*/

  bme_out.settings.commInterface = I2C_MODE;  // I have worked with the example of http://gilles.thebault.free.fr/
  bme_out.settings.I2CAddress = 0x76;
  bme_out.settings.runMode = 3; 
  bme_out.settings.tStandby = 0;
  bme_out.settings.filter = 0;
  bme_out.settings.tempOverSample = 1 ;
  bme_out.settings.pressOverSample = 1;
  bme_out.settings.humidOverSample = 1;
  delay(10); 
  bme_out.begin();  

}

void loop() {


  get_sensors();// Lecture du programme d'aquisition de la température et de l'humidité

  fan_control();// Appel du programme de gestion du niveau de ventilation
  recep(); // vérifi l'arrivée de nouveaux messages
  
  wdt_reset();

  
}

 /************************************************************************************
    
    <VMC speed control, remote>
    Copyright (C) <2019>  <Fabrice BAUDIN>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    info@InnoGreenTech.fr

****************************************************************************************//*******************************/

/*******************************
 *     Utility library         *
 *******************************/
    
    
    #include <registers.h>          
    #include <pin_magic.h>
    #include  <printf.h>
    
/*******************************
 *     Set modul radio         *
 *******************************/
 
    #include  <nRF24L01.h>
    #include  <RF24.h>
    #include  <RF24_config.h>
    #define   CERF 49               
    #define   CSRF 48 
    RF24 radio(CERF,CSRF);      // define object
    
    byte trans[5] ;             // arrow for datas
    long donnee;                // data
    byte type_requiest;                // type of requiest

/************************
 *    EEPROM  ADDRESS   *
 ************************/

    #include <EEPROM.h>
    
    #define MEM_MODE                         0   // adresse sauvegarde MC_MEM
    #define MEM_SETTING_SUMMER_TEMPERATURE   4   // adresse sauvegarde consigne température ETE
    #define MEM_SETTING_WINTER_TEMPERATURE   8   // adresse sauvegarde consigne température hivers
    #define MEM_SETTING_SUMMER_HUMIDITY     12   // adresse sauvegarde consigne Humidité ETE
    #define MEM_SETTING_WINTER_HUMIDITY     16   // adresse sauvegarde consigne   Humidité Hive
    #define MEM_SETTING_CO2                 20   // Adresse sauvegarde consigne  qualité de l'aire
    #define MEM_SETTING_ALTITUDE            24   // Altitude memory

    
/**************************
 *      Screen setting    *
 **************************/

    #include <Adafruit_GFX.h>       // Librairie pour dessin
    #include <Fonts/WeatherIcon.h>
    #include <Adafruit_GFX.h>       // Librairie pour dessin
    //#include <Adafruit_TFTLCD.h>  //librairie de configuration Ã©cran
    #include <MCUFRIEND_kbv.h>      //librairie de configuration Ã©cran HX8347
    MCUFRIEND_kbv tft;

    
    /* Pin setting */
    
    #define LCD_CS A3             // Chip Select goes to Analog 3
    #define LCD_CD A2             // Command/Data goes to Analog 2
    #define LCD_WR A1             // LCD Write goes to Analog 1
    #define LCD_RD A0             // LCD Read goes to Analog 0
    #define LCD_RESET A4          // Peut être raccordé à la pin reset de l'arduino


    /* Define colors */
    #define RGB565(R,G,B) ((((unsigned int)R&0xF8)<<8) | (((unsigned int)G&0xFC)<<3) | ((unsigned int)B>>3))  // Macro to convert couleur 24 bit

    #define BLACK   0x0000
    #define BLUE    0x001F
    #define RED     0xF800
    #define GREEN   0x07E0
    #define CYAN    0x07FF
    #define MAGENTA 0xF81F
    #define YELLOW  0xFFE0
    #define ORANGE  0xFD20 
    #define WHITE   0xFFFF
    #define BROWN   RGB565(165,175,143)
    
    #define FOND    0x0000        // Back colors

    //Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


/**********************************
*            Create buttons       *
***********************************/


    
    Adafruit_GFX_Button four_buttons[4];                     //création de 4 boutons pour l'écran d'accueil
    char main_buttons[4][4]={"IN","OUT","POW","INF"};    //nom des boutons de la page d'acceuil
    
    #define INF 3                                      // bouton de paramétrage
    #define IN  0                                      // VMC Page
    #define OUT  1                                      // Bouton de réglage de l'humidité
    #define POW  2                                      // Bouton d'accés au réglage de la qualité de l'air
  
    char setting_buttons[4][4]={" + ","OK"," - ","ESC"};
    #define LESS  2             // Button Moins
    #define OK    1             // Button OK
    #define MORE  0             // Button PLUS
    #define ESC   3             // Button END

    
    Adafruit_GFX_Button two_buttons[2];
    
    char second_buttons[2][8]={"Escape","Setting"}; 
    #define ESCAPE      0           // Button for screen of greenhouse
    #define SETTING     1           // Button for screen of compost

    char choice_buttons[2][5]={"UP","DOWN"}; 
    #define UP          0           // Button for screen of greenhouse
    #define DOWN        1           // Button for screen of compost

    Adafruit_GFX_Button six_buttons[6]; 
                      
    char mode_buttons[6][6]={"Stop","Hiver","Ete","V1","V2","V3"};
    
    #define STOP_VMC                      0           
    #define WINTER_MODE                   1           
    #define SUMMER_MODE                   2           
    #define SPEED_1                       3           
    #define SPEED_2                       4          
    #define SPEED_3                       5         


/*************************
 *   Set touch screen    *
 *************************/
     
    #include <TouchScreen.h>          
    
    #define YP A3                     // must be an analog pin, use "An" notation!
    #define XM A2                     // must be an analog pin, use "An" notation!
    #define YM 9                      // can be a digital pin
    #define XP 8                      // can be a digital pin
    
    #define TS_MINX 70                // Valeur minimun de la position en x
    #define TS_MAXX 920               // Valeur maximum de la position en x
    #define TS_MINY 70                // Valeur Minimum de la position en Y
    #define TS_MAXY 920               // Valeur maximum de la position en z
    
    TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); 

    int x=0; // valeur X d'appui tactil
    int y=0; // valeur y d'appui tactil
    int z=0; // intensitée d'appui
    
    unsigned long button_delay;          // delay of push buttom
    #define BUTTON_DELAY 200    // delay filter for the buttom 
    
    #define DELAY_REFRESH_SCREEN         5000
    #define DELAY_REFRESH_SCREEN_SECONDS 5
    unsigned long refresh_datas=0;   // delay to refresh screen and data, every 10 seconds*
    
    byte          refresh_demand=1;
    #define       REFRESH_SCREEN    0  
    #define       REFRESH_DATA      1   
    #define       UPDATE_SCREEN     2


/************************************************
 *                Watch doog                    *
 ************************************************/

    #include <avr/wdt.h>

 
/***********************************************
 *               Ram setting                   *
 ***********************************************/



    byte flag_screen=B00000001;     // drapeaux de demande d'écran, acceuil par défaut
    byte flag_first_screen=B00000000;     // drapeaux de premiére lecture
    
    #define MAIN_SCREEN        0                  // Drapeau de l'écran d'acceuil
    #define IN_SCREEN          1                  // Drapeau de demande de réglage consigne température
    #define OUT_SCREEN         2                  // Drapeau de demande de réglage consigne Humidité
    #define POWER_SCREEN       3                  // Drapeau de demande de réglage consigne qualité de l'air
    #define SETTING_SCREEN     4                  // Drapeau de demande de rafraichissement des valeurs lu
    #define INFORMATION_SCREEN 5

    byte index_setting;                         //Index to change value or parameter
    int  setting;
    byte new_index;
    byte new_setting;
    byte reset_demand=0;

    byte flag=0;                   // Registre utilitaire,
    
    #define MODE_CONSIGNE 0       // Choix de quelle consigne doit être réglée (hivers/été)
    #define MODE_CONSIGNE_BK 1    // Valeur de la consigne précédente
    #define PUSH_BUTTON 2        // Passe à un lors d'appui sur un bouton remi à zero au bout de 4 milliseconde
    #define LCD_ARRET 3           // écran Lcd à l'arrêt



    int   set_temperature_summer; // Consigne de température, été
    int   set_temperature_winter; //Hivers
    int   set_humidity_summer; //Consigne d'humidité, été
    int   set_humidity_winter; // hivers
    int   set_co2; // Consigne de qualité de l'air
    int   set_mode;//MODE de fonctionnement
    int   set_altitude;//MODE de fonctionnement
    
    float tIn;      // Variable Température intérieur
    long  hIn;      // Variable humidité intérieur
    long  qIn;      // Variable de la qualité de l'air intérieur
    
    float tOut;     // Variable température extérieur
    long  hOut;     // Variable humidité extérieur
    long  pOut;     // Pression Extérieur
    
    long  venti;    // Valeur de la ventilation actuelle;
    float u;        // Tension du réseau électrique en volts
    float i;        // Courant consommée
    long  p;        //Puissance instantanée consommée
    long  e;        //Energie totale consommée
    float tsalon;   // Température du salon
    
    float consigne; // Variable des consignes

/* meteo memory */
    #define         NUMBER_SAMPLES_HOUR 12
    
    float           average_pressure[NUMBER_SAMPLES_HOUR];            // take x samples per hour
    float           current_average_pressure;
    int             total_samples_pressure=int((3600/DELAY_REFRESH_SCREEN_SECONDS)/NUMBER_SAMPLES_HOUR);
    int             current_sample_pressure;
    byte            rotate_index=0;     

    byte current_weather=1;
    byte forecasts_weather=1;
    byte last_forecasts_weather=10;
    #define STABLE             0
    #define SUNNY              1
    #define CLOUDLY            2
    #define RAIN               3
    #define THUNDERSTORM       4
    #define UNKNOWN            5

    char weather_string[4]={char(49),char(51),char(56),char(56)};

/* String for commnunication with ESP8266 */

    String  date;             
    String  hour;         
    String  ip_address;      
    String  gate_way; 
    String  mac_address;    

/*********************************************************
 *  Key of communication between Arduino and ESP8266     *
 *********************************************************/

    int index_sent=0;                           //allow to sent data one by one with PERIOD_SENT bettween each
    #define PERIOD_SENT 100                     //one information every 100 ms;
    unsigned long period_sent=0;                //control the last message
    unsigned long number_of_samples;            //Number of samples between two sender 


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
    


    // Tableau pour récuper les inforamations radio
    
    byte code[18]={ 
                   CODE_TENSION,
                   CODE_COURANT,
                   CODE_PUISSANCE,
                   CODE_CONSOMMATION,
                   CODE_TEMPERATURE_OUT,
                   CODE_HUMIDITY_OUT,
                   CODE_PRESSURE,
                   CODE_TEMPERATURE_IN,
                   CODE_HUMIDITY_IN,
                   CODE_CO2,                   
                   CODE_SPEED_FAN,
                   CODE_MODE,
                   CODE_SET_TEMPERATURE_SUMMER,
                   CODE_SET_TEMPERATURE_WINTER,
                   CODE_SET_HUMIDITY_SUMMER,
                   CODE_SET_HUMIDITY_WINTER,
                   CODE_SET_CO2,
                   CODE_SET_ALTITUDE 
                    };                 // Tableau des données (read/write)
    
    int index=0;                        //Index de la demande actuel

    void(* resetFunc) (void) = 0;                   //declare reset function at address 0

/************************************************
*           Initialisation                      *
*************************************************/

void setup(void){


   /* Setting screen */

    tft.reset(); // intialisation de l'écran
  
    
    uint16_t identifier=0x9341;   //Driver 9341 (voir librairies )
    tft.begin(identifier);        //configuration de la librairie
    tft.setRotation(135);         //mise en place l'écran en MC_MEM paysage





    /*  Read eeprom */

    byte mem[4]; // Tableau pour réintégration des mems
    long rsave;
    
    for (int a=0;a<2;a++){mem[a]= EEPROM.read (MEM_MODE +a);}// MC_MEM de fonctionnement
    set_mode=(int)mem[0]|(int)mem[1]<<8;
    
    
    for (int a=0;a<2;a++){mem[a]= EEPROM.read (MEM_SETTING_SUMMER_TEMPERATURE+a);}// Consigne température d'été
    set_temperature_summer= (int)mem[0]|(int)mem[1]<<8;
    if (set_temperature_summer>99||set_temperature_summer<-99){set_temperature_summer=99;}
    
    
    for (int a=0;a<2;a++){mem[a]= EEPROM.read (MEM_SETTING_WINTER_TEMPERATURE+a);}// Consigne température d'hiver
    set_temperature_winter= (int)mem[0]|(int)mem[1]<<8;
    if (set_temperature_winter>99||set_temperature_winter<-99){set_temperature_winter=99;}
    
    for (int a=0;a<2;a++){mem[a]= EEPROM.read (MEM_SETTING_SUMMER_HUMIDITY+a);}// Consigne humidité d'été
    set_humidity_summer=(int)mem[0]|(int)mem[1]<<8;
    if (set_humidity_summer>99||set_humidity_summer<-99){set_humidity_summer=99;}
    
    for (int a=0;a<2;a++) {mem[a]= EEPROM.read (MEM_SETTING_WINTER_HUMIDITY +a);}// Consigne humidité d'hiver
    set_humidity_winter=(int)mem[0]|(int)mem[1]<<8;
    if (set_humidity_winter>99||set_humidity_winter<-99){set_humidity_winter=99;}
    
    for (int a=0;a<2;a++) {mem[a]= EEPROM.read (MEM_SETTING_CO2 +a);}// Consigne qualité
    set_co2=(int)mem[0]|(int)mem[1]<<8;
    if (set_co2>10000||set_co2<0){set_co2=1000;}

    for (int a=0;a<2;a++) {mem[a]= EEPROM.read (MEM_SETTING_ALTITUDE +a);}// Consigne qualité
    set_altitude=(int)mem[0]|(int)mem[1]<<8;
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
    radio.openWritingPipe((byte*)"Cent1");// Ecrit depuis l'adresse base
    radio.openReadingPipe(1,(byte*)"1node");// Ecoute l'adresse du gestionnaire de VMC
    radio.openReadingPipe(2,(byte*)"2node");// Ecoute de l'adresse du contrôleru de consommation
    radio.setAutoAck(false);   // Désactivation de l'accusé de réception
    radio.enableDynamicAck();  // Déasactivation de l'accusé de réception
    //attachInterrupt(2,recep,LOW); // Activation des interruptions pour la réception des messages sur pin 21
    //radio.maskIRQ(1,1,0);   // N'accepte que les interruption de lecture
    radio.startListening(); // Mise en écoute du module radio


/* Start  watch doog */

  wdt_reset();
  bitClear(MCUSR, WDRF);            // Reset du chien de garde
  WDTCSR = (1 << WDCE) | (1 << WDE);   //  Demande de réglage d
  WDTCSR =(1<<WDIE)| (1 << WDE)| (0<<WDIF) | (1 << WDP3) | (0 << WDP2)| (0 << WDP1)| (1<< WDP0) ; // Activation Delay 1 seconde
  
  
  

/* Start serial communication */

   Serial.begin(9600);
   Serial2.begin(115200);



}

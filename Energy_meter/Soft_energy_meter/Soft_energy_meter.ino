 /************************************************************************************
    
    <Energy meter for home controller, vmc project,>
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
/* Configuration du wattmètre 

#include <SoftwareSerial.h> // Arduino IDE <1.6.6
#include <PZEM004T.h>


PZEM004T pzem(7,8);  // (RX,TX) connect to TX,RX of PZEM

IPAddress ip(192,168,1,1); */

#include <PZEM004Tv30.h>

PZEM004Tv30 pzem(7, 8);

float v;  // valeur de la tension
float i;  // Valeur du courant
long  p;  //puissance instantanée
long  e;    //puissance consommée

/* Configuration de l'écran */


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET A3
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

unsigned long refreshScreen;      // taux de rafraîchissement de l'écran
#define REFRESH 1000

/* Configuration de la radion RF */


#include <nRF24L01.h>
#include <SPI.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#define  CERF 10             // Définition de la pin Enable
#define  CSRF 9               // Définition de la pin Sélection,
RF24     radio(CERF,CSRF);        // Entrée des informations dans la librairie


/********variable d'échange avec la carte mére*******************/

byte trans[5] ; // Tableau pour la trans mission de données
long donnee; //Valeur de la donnée transmise
byte nature; // lecture de la nature de la demande de la carte mére
// variable d'échange avec la carte mére

#define CODE_TENSION 10           // Tension électrique du réseau
#define CODE_COURANT 11           // Courant absorber par le réseau électrique
#define CODE_PUISSANCE 12         // Puissance active absorbée
#define CODE_CONSOMMATION 13      // Consommation d'énergie
#define CODE_TEMPEXT 14          // Température extérieur
#define CODE_HUMEXT  15           // Humidité extérieur
#define CODE_TEMVENT 16           //Température de ventillation
#define CODE_HUMVENT 17           //Taux d'humidité de l'air ventilé
#define CODE_QUALVENT 18          //Qualité de l'air extrait
#define CODE_VITVENT 19           //Vitesse de la ventilation forcée
#define CODE_TEMPSAL 20          //Température du salon
#define CODE_LECTURE 21      //  Demande de renvoyer les valeurs calculer (information non obligatoir)
#define CODE_CALIBRATION 22  //  Demande de calibration (information= 1 pour intérieur, 2 pour extérieur)
#define CODE_TEC 23 // Envoi consigne de température été
#define CODE_THC 24 // Envoi consigne de température hivers
#define CODE_HEC 25// Envoi consigne d'humidité été
#define CODE_HHC 26 // Envoi consigne d'humidité hivers
#define CODE_QC 27 // Envoi consigne de qualité
#define CODE_MC 28 // Envoi mode de fonctionnement



void setup() {
  delay(250);
  Serial.begin(9600);

 // pzem.setAddress(ip);
  

  // Mise en service de l'affichage
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  display.clearDisplay();
  display.display();



// configuration de la radio

noInterrupts();
radio.begin();                            //Allumage radio
//radio.enableDynamicPayloads();
radio.disableDynamicPayloads();
radio.setRetries(5,0);                    // délais (Nbx250 usec Nombre de tentatives d'envoi message
radio.setChannel(90);                     //canal de diffusion
radio.setPayloadSize(5);                  //taille des messages de 5 Bytes 1 pour information 2 pour valeur int
radio.setPALevel(RF24_PA_HIGH);           // niveau d'emission
radio.setDataRate(RF24_250KBPS);            // vitesse de transmission
radio.openWritingPipe((byte*)"2node");    // Ecrit depuis l'adresse du compteur d'énergie
radio.openReadingPipe(1,(byte*)"Cent1");  // Ecoute l'adresse de la base
radio.setAutoAck(false);
radio.enableDynamicAck();
//radio.maskIRQ(1,1,0);                   // N'accepte que les interruption de lecture
//attachInterrupt(1,recep, LOW);          // Activation des interruptions pour la réception des messages sur pin 3 
radio.startListening();                   //Mise en écoute du module*/
interrupts();

}


void loop() {
recep();
if (millis()>refreshScreen+REFRESH)
  {
      display.clearDisplay(); 
      display.setTextSize(2);
      display.setTextColor(BLACK, WHITE);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      v = pzem.voltage();
      if (v < 0.0) v = 0.0;
      display.print(v);display.println(" V");

      i = pzem.current();
      display.print(i);display.println(" A"); 
      
      p = pzem.power();
      display.print(p);display.println(" W"); 
      
      e = pzem.energy();
      float ke= float(e)/1000;
      display.print((ke));display.println(" kWh"); 
      display.display();
      refreshScreen=millis();
  }

}

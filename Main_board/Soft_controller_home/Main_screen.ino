
/*********************************
*            main_screen         *
**********************************/

void main_screen(){

 

/*********************************************************************************************************************************
* Création de l'arriére plan à la premiére lecture
*/


if (!bitRead(flag_first_screen,MAIN_SCREEN)){// Si premiére lecture

 
  tft.fillScreen(FOND);// Fond d'écran Noir
  



         
  /*tft.setTextColor(WHITE); // texte de couleur blanche
  tft.setTextSize(3); // Taille du texte
  tft.setCursor(8,10); // Ecriture de l'information permanente VMC
  tft.print("VMC:");*/
  
  /* Drawing house*/
    
      for (int i=0; i<3; i++){
        tft.drawLine(10, 60+i, 85, 10+i, CYAN);
        tft.drawLine(85, 10+i, 160, 60+i, CYAN);
        tft.drawFastVLine(20+i,70,105,CYAN);
        tft.drawFastVLine(150+i,70,105,CYAN);
        tft.drawFastHLine(20,175+i,132,CYAN);
      }



/* Write Bottons */
    main_buttons_design();
    
    bitSet(flag_first_screen,MAIN_SCREEN); 
    last_forecasts_weather=10;

    } // End of background 

    
    
/****************************************************
 *                Write  information                *
 ****************************************************/

if(bitRead(refresh_demand,REFRESH_SCREEN)){
  

     int colour=0;
     tft.setFont();
     tft.setTextSize(2); // Taille de L'écriture
     tft.setTextColor(WHITE,FOND); // Couleur du texte
     
     tft.setCursor(45,80);  // mise en place du curseur
     /*if(30>tIn and tIn>18) {colour = 127 <<5 | int( map(tIn,18,30,0,31))<<12;}
     else if(tIn>30){colour= int( map(tIn,30,40,127,0))<<5 | 31 << 12;}
     else {colour= int(map(tIn,18,0,127,0))<<5 | 31 << 12;}*/

     tft.setTextColor(WHITE,FOND);
     tft.print(tIn);tft.print(" \xF7\C"); // Ecriture de la température
     tft.setCursor(45,105);
     
     /*if(50>hIn>=40) {colour= 127<<5 | int(map(hIn,40,50,0,31)<<12);}
     else if(hIn>=50){colour= int(map(hIn,50,60,127,0))<<5 | 31 << 12;}
     else if (40>hIn>30){colour= 127<<5 | int(map(hIn,40,30,0,31)<<12);}
     else{colour= int(map(hIn,30,20,127,0))<<5 | 31 << 12;}*/
     tft.setTextColor(WHITE,FOND);
     tft.print(hIn);tft.print(" % ");

     
     if(qIn<800) {colour= 127<<5 | int(map(qIn,400,800,0,31))<<12;}
     else{colour= int(map(qIn,800,1000,127,0))<<5 | 31 << 12;}
     tft.setTextColor(colour,FOND);
     tft.setCursor(45,130);// écriture de la qualité général de l'air
     tft.print(qIn);tft.print(" ppm");

     
     if(p<500) {colour= 127<<5 | int(map(p,100,500,0,31))<<12;}
     else{colour= int(map(p,500,3000,127,0))<<5 | 31 << 12;}
     tft.setTextColor(colour,FOND);
     tft.setCursor(45,155);
     tft.print(p);tft.print(" W ");

// Affichage des donnée extérieurs
    
     tft.setTextColor(WHITE,FOND);

     if (last_forecasts_weather!=forecasts_weather)
     {
      tft.setFont(&Weathericon);   
      tft.setCursor(220,100);
      tft.fillRect(200,50,100,50,BLACK);      
      tft.print (weather_string[forecasts_weather-1]);
      last_forecasts_weather=forecasts_weather;
     }
     
    tft.setFont();
    tft.setCursor(180,10);
    tft.print(date);
    tft.setCursor(180,35);
    tft.print(hour);
    



    tft.setCursor(200,110);  // mise en place du curseur
    tft.print(tOut);tft.print(" \xF7\C "); // Ecriture de la température
    tft.setCursor(200,135);
    tft.print(hOut);tft.print(" % ");
    tft.setCursor(200,160);          
    tft.print(pOut);tft.print(" mb ");


     
// Affichage niveau de ventilation


     tft.drawRoundRect(60, 35, 50, 30, 3, CYAN);
     
     for ( int x=1; x<=venti; x++){
      tft.fillRect(55+13*x,40,9,20,CYAN);
     }
     for ( int x=3; x>venti; x--){
      tft.fillRect(55+13*x,40,9,20,BLACK);
     }
     for ( int x=1; x<=3; x++){
      tft.drawRect(55+13*x,40,9,20,CYAN);
     }
      
}
   

    
/***********************************************************************************************************************************  
* IN screen activation
*/
  
  if (four_buttons[IN].contains(x,y))
    { 
      flag_screen=0;  
      flag_first_screen=0;
      refresh_demand=2;
      bitSet(flag_screen,IN_SCREEN); 
     }

/**************************************************************************************************************************************  
* out screen activation
 */
 
  if (four_buttons[OUT].contains(x,y))
    { 
      flag_screen=0;  
      flag_first_screen=0;
      refresh_demand=2;
      bitSet(flag_screen,OUT_SCREEN); 
     }
  
/***********************************************************************************************************************************
* Power screen activation
*/
 
  if (four_buttons[POW].contains(x,y))
    { 
      flag_screen=0;  
      flag_first_screen=0;
      refresh_demand=2;
      bitSet(flag_screen,POWER_SCREEN); 
     }

/***********************************************************************************************************************************
* Information screen activation
*/
 
  if (four_buttons[INF].contains(x,y))
    { 
      flag_screen=0;  
      flag_first_screen=0;
      refresh_demand=2;
      bitSet(flag_screen,INFORMATION_SCREEN); 
     }

   y=0;
   x=0;  
 
}
  

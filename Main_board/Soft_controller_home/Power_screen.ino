void power_screen(){
 if (!bitRead(flag_first_screen,INFORMATION_SCREEN)){   // If it is the first read

      tft.fillScreen(FOND);
      tft.setTextColor(WHITE);
      tft.setTextSize(2);
      tft.setCursor(8,10);
      tft.print F("Consommation electrique");
      

      tft.setCursor(8,50);
      tft.print F("Puissance :"); 
      tft.setCursor(150,50);  
      tft.print(p);tft.print(" W    ");
      tft.setCursor(8,85); 
      tft.print F("Tension :");
      tft.setCursor(150,85);  
      tft.print(u);tft.print(" V   ");
      tft.setCursor(8,120); 
      tft.print F("Courant :");
      tft.setCursor(150,120);  
      tft.print(i);tft.print(" A  ");

 


/* Create Buttons */

      second_buttons_design();
     
     bitSet(flag_first_screen,INFORMATION_SCREEN); 
}
  


  if (two_buttons[ESCAPE].contains(x,y)){       
      flag_screen=0;  
      flag_first_screen=0;
      bitSet(flag_screen,MAIN_SCREEN);              //call main screen 
      bitSet(refresh_demand,REFRESH_SCREEN);  
      }


 
  if (two_buttons[SETTING].contains(x,y)){  
      flag_screen=0;  
      flag_first_screen=0;
      index_setting=1;
      new_index=0;
      bitSet(flag_screen,SETTING_SCREEN);              //call setting screen to set WIFI
        }
      


          y=0;
          x=0;              
}

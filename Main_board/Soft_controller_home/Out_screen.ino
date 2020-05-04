void out_screen(){

  if (!bitRead(flag_first_screen,INFORMATION_SCREEN)){   // If it is the first read

      tft.fillScreen(FOND);
      tft.setTextColor(WHITE);
      tft.setTextSize(2);
      tft.setCursor(8,10);
      tft.print F("Outdoor information");
      
      tft.setTextSize(1);
      tft.setCursor(8,45);
      tft.print F("Meteo actuelle:"); 
      tft.setCursor(8,65); 
      tft.print F("Tendance Meteo:");
      tft.setFont(&Weathericon);
      tft.setCursor(100,60); 
      tft.print (weather_string[current_weather-1]);
      tft.setCursor(100,80); 
      tft.print (weather_string[forecasts_weather-1]); 
      tft.setFont();
      tft.setCursor(8,85); 
      tft.print F("Temperature :");
      tft.setCursor(100,85); 
      tft.print(tOut);tft.print(" \xF7\C");
      tft.setCursor(8,105);
      tft.print F("Humidite :");
      tft.setCursor(100,105);
      tft.print(hOut);tft.print(" % "); 
      tft.setCursor(8,125); 
      tft.print F("Pression :");
      tft.setCursor(100,125); 
      tft.print(pOut);tft.print(" mbar");

 


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

void in_screen(){

  /**************************************************************************************************************************************  
*                     Mode buttons controle
 */
  for (int a=0; a<6; a++){
      if (six_buttons[a].contains(x,y))
        {   
          if (a<3){set_mode=a;}
          else{set_mode=a+1;}
          sent_rf(long(set_mode),CODE_MODE);
          int  mode=set_mode; 
          for (int a=0;a<2;a++){EEPROM.write(MEM_MODE+a ,mode);mode=mode>>8;}          
          mode_buttons_design();
        }
    }

  if (!bitRead(flag_first_screen,INFORMATION_SCREEN)){   // If it is the first read

      tft.fillScreen(FOND);
      tft.setTextColor(WHITE);
      tft.setTextSize(2);
      tft.setCursor(8,10);
      tft.print F("Information Indoor");
      
      tft.setTextSize(1);
      tft.setCursor(8,45);
      tft.print F("Temperature:"); 
      tft.setCursor(8,60);  // mise en place du curseur
      tft.print(tIn);tft.print(" \xF7\C");
      tft.setCursor(8,80); // Therme générique de la qualité
      tft.print F("Humidite :");
      tft.setCursor(8,95);  // mise en place du curseur
      tft.print(hIn);tft.print(" % "); 
      tft.setCursor(8,115); // Therme générique de la qualité
      tft.print F("CO2 :");
      tft.setCursor(8,130);  // mise en place du curseur
      tft.print(qIn);tft.print(" ppm");

 


/* Create Buttons */

      second_buttons_design();
      mode_buttons_design();
     
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

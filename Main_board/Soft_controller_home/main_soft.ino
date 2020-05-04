/***************************************
*     Programme Principal              *
****************************************/

void loop(void){

  if (bitRead(refresh_demand,UPDATE_SCREEN)){bitSet(refresh_demand,REFRESH_SCREEN);}
   
  if (millis()>refresh_datas+DELAY_REFRESH_SCREEN){              // demand a refresh screen and lecture of sensor
      bitSet(refresh_demand,REFRESH_DATA);
      bitSet(refresh_demand,REFRESH_SCREEN);                  
      refresh_datas=millis();
      weather();
      /*tft.write_inno(0x53,0x42);
      tft.write_inno(0x51,0x00);*/
      
      /* Serial.print("configuration mode éclairage: ");Serial.println(tft.readReg(0x54), HEX);
      Serial.print("réglage mode éclairage: ");Serial.println(tft.readReg(0x52), HEX);*/
      //tft.write_inno(0x26,0x01);

    } 
  
  
  tactil ();  
  recep_wifi();
  tactil (); 
  send_data();
  tactil (); 

   switch(flag_screen){

             case B00000001:
                main_screen();
                break;

             case B00000010:
                in_screen();
                break;
        
             case B00000100:
                out_screen();
                break;
  
             case B00001000:
                power_screen();
                break;

             case B00010000:
                setting_screen();
                break; 
             case B00100000:
                information_screen();
                break;                           

             default:
                main_screen();
                break;
            }


 if(bitRead(refresh_demand,REFRESH_SCREEN)){bitClear(refresh_demand,REFRESH_SCREEN);}
 if(bitRead(refresh_demand,REFRESH_DATA)){bitClear(refresh_demand,REFRESH_DATA);}
  wdt_reset();
}

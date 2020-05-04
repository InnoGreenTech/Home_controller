void recep(){
  

if (radio.available()){

         long information;
        
         radio.read(&trans,5);
         nature=trans[4];                                            // lecture du byte de commande
         
         donnee= (long)trans[0]|(long)trans[1]<<8|(long)trans[2]<<16|(long)trans[3]<<24;

         //Serial.println(nature); 
         switch(nature){

          
    
              case CODE_TEMPERATURE_OUT:             // external temperature
                     information=long(tOut*100);
                     //Serial.println("Reception temperature");
                     envoi(information,CODE_TEMPERATURE_OUT);
                     break;

              case CODE_HUMIDITY_OUT :              // external Humidity 
                     information=long(hOut);
                     envoi(information,CODE_HUMIDITY_OUT);
                     break;
                     
              case CODE_TEMPERATURE_IN :             // airing temperature
                    information=long(tIn*100);
                    envoi(information,CODE_TEMPERATURE_IN);
                    break;
                    
              case CODE_HUMIDITY_IN :           // airing Humidity
                    information=long(hIn);
                    envoi(information,CODE_HUMIDITY_IN);
                    break;
                    
              case CODE_CO2 :          // airing Quality
                    information=long(qIn);
                    envoi(information,CODE_CO2);
                    break;
                         
             case CODE_SPEED_FAN :             // airing speed
                    information=long(venti);
                    envoi(information,CODE_SPEED_FAN);
                    break;
                    
             case CODE_PRESSURE:        // Calibration quality
                    information=long(pOut);
                    envoi(information,CODE_PRESSURE);
                    break;
                    
             case CODE_SET_TEMPERATURE_SUMMER:
              
                    if (donnee!=long(set_temperature_summer*100))
                    { 
                        //Serial.println("write EEPROM !!");
                        set_temperature_summer=float(donnee/100); 
                        for (int a=0;a<4;a++){EEPROM.write(MEM_SETTING_SUMMER_TEMPERATURE+a,donnee);donnee=donnee>>8;}
                    }
                    break;
                    
             case CODE_SET_TEMPERATURE_WINTER :              // Set winter temperature
                    if (donnee!=long(set_temperature_summer*100))
                    { 
                        //Serial.println("write EEPROM !!");
                        set_temperature_summer=float(donnee/100); 
                        for (int a=0;a<4;a++){EEPROM.write(MEM_SETTING_WINTER_TEMPERATURE+a,donnee);donnee=donnee>>8;}
                    }
                    break;
                    
             case CODE_SET_HUMIDITY_SUMMER :             // Set summer Humidity
                    if (donnee!=long(set_humidity_summer))
                    { 
                        //Serial.println("write EEPROM !!");
                        set_humidity_summer=donnee; 
                        for (int a=0;a<4;a++){EEPROM.write(MEM_SETTING_SUMMER_HUMIDITY+a,donnee);donnee=donnee>>8;}
                    }             
                    break;

             case CODE_SET_HUMIDITY_WINTER :            // Set winter humidity
                    if (donnee!=set_humidity_winter)
                    { 
                        //Serial.println("write EEPROM !!");
                        set_humidity_winter=donnee; 
                        for (int a=0;a<4;a++){EEPROM.write(MEM_SETTING_WINTER_HUMIDITY+a,donnee);donnee=donnee>>8;}
                    }             
                    break;                   

              

             case CODE_MODE :              // Set Mode of work
                    if (donnee!=set_mode)
                    { 
                        //Serial.println("write EEPROM !!");
                        set_mode=donnee; 
                        for (int a=0;a<4;a++){EEPROM.write(MEM_MODE+a,donnee);donnee=donnee>>8;}
                    }             
                    break;

             case CODE_SET_CO2:

                    if (donnee!= set_co2)
                    {
                      set_co2=donnee;
                      for (int a=0;a<4;a++){EEPROM.write(MEM_SETTING_CO2+a,donnee);donnee=donnee>>8;}
                    }

             case CODE_SET_ZERO_CO2:
                    if (donnee==1){
                      manu_cali();
                      zero_CO2();
                    }
                    else if(donnee==0){ini_CO2();}
                    break;
                    
             default :
                  break;
         }
        
         }

         }

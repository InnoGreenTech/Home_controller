void config_probe(){

      int id_probe=0;


      if ( server.hasArg("id_prob") ) 
              {      
              reception=server.arg("id_prob");
              id_probe=reception.toInt();
              }
      else {return;}         


      if (id_probe==1)
            { 
              if ( server.hasArg("off_set") )
              {
              reception = server.arg("off_set");
              t_offset=reception.toInt();
              int b=h_offset;
              for (int a=0;a<2;a++){EEPROM.write(TEMPERATURE_OFFSET+a ,b);b=b>>8;}
              } 

            
              if ( server.hasArg("max") )
              {
              reception = server.arg("max");
              t_max=reception.toInt();
              int b=t_max;
              for (int a=0;a<2;a++){EEPROM.write(TEMPERATURE_MAX+a ,b);b=b>>8;}
              }   

              if ( server.hasArg("min") )
              {
              reception = server.arg("min");
              t_min=reception.toInt();
              int b=t_min;
              for (int a=0;a<2;a++){EEPROM.write(TEMPERATURE_MIN+a ,b);b=b>>8;} 
              } 

              if ( server.hasArg("alarm") )
              {
              reception=server.arg("alarm");
              if (reception.equals("1")) {bitSet(activation_alarmes, ALARME_T);}  // Active alarm
              else {bitClear(activation_alarmes, ALARME_T);}                       
              EEPROM.write(ALARME_EEPROM, activation_alarmes); 
              }
            }    
        

      if (id_probe==2)
           { 
              if ( server.hasArg("offset") )
              {
              reception = server.arg("offset");
              h_offset=reception.toInt();
              int b=h_offset;
              for (int a=0;a<2;a++){EEPROM.write(HUMIDITE_OFFSET+a ,b);b=b>>8;}
              } 
            
              if ( server.hasArg("max") )
              {
              reception = server.arg("max");
              h_max=reception.toInt();
              int b=h_max;
              for (int a=0;a<2;a++){EEPROM.write(HUMIDITE_MAX+a ,b);b=b>>8;}
              }   

              if ( server.hasArg("min") )
              {
              reception = server.arg("min");
              h_min=reception.toInt();
              int b=h_min;
              for (int a=0;a<2;a++){EEPROM.write(HUMIDITE_MIN+a ,b);b=b>>8;} 
              }

              
              if ( server.hasArg("alarm") )
              {
              reception=server.arg("alarm");
              if (reception.equals("1")) {bitSet(activation_alarmes, ALARME_H);}  // Active alarm
              else {bitClear(activation_alarmes, ALARME_H);}                       
              EEPROM.write(ALARME_EEPROM, activation_alarmes); 
              }                            
           }

     if (id_probe==4)
           { 
              if ( server.hasArg("offset") )
              {
              reception = server.arg("offset");
              c_offset=reception.toInt();
              int b=c_offset;
              for (int a=0;a<2;a++){EEPROM.write(COUNT_OFFSET+a ,b);b=b>>8;}
              } 
            
              if ( server.hasArg("max") )
              {
              reception = server.arg("max");
              c_max=reception.toInt();
              int b=c_max;
              for (int a=0;a<2;a++){EEPROM.write(COUNT_MAX+a ,b);b=b>>8;}
              }   

              if ( server.hasArg("min") )
              {
              reception = server.arg("min");
              c_min=reception.toInt();
              int b=c_min;
              for (int a=0;a<2;a++){EEPROM.write(COUNT_MIN+a ,b);b=b>>8;} 
              }

              
              if ( server.hasArg("alarm") )
              {
              reception=server.arg("alarm");
              if (reception.equals("1")) {bitSet(activation_alarmes, ALARME_C);}  // Active alarm
              else {bitClear(activation_alarmes, ALARME_C);}                       
              EEPROM.write(ALARME_EEPROM, activation_alarmes); 
              }                        
           }

if (id_probe==3)
           { 
              if ( server.hasArg("off_set") )
              {
              reception = server.arg("offset");
              l_offset=reception.toInt();
              int b=l_offset;
              for (int a=0;a<2;a++){EEPROM.write(LEVEL_OFFSET+a ,b);b=b>>8;}
              } 
            
              if ( server.hasArg("max") )
              {
              reception = server.arg("max");
              l_max=reception.toInt();
              int b=l_max;
              for (int a=0;a<2;a++){EEPROM.write(LEVEL_MAX+a ,b);b=b>>8;}
              }   

              if ( server.hasArg("min") )
              {
              reception = server.arg("min");
              l_min=reception.toInt();
              int b=l_min;
              for (int a=0;a<2;a++){EEPROM.write(LEVEL_MIN+a ,b);b=b>>8;} 
              }

              
              if ( server.hasArg("alarm") )
              {
              reception=server.arg("alarm");
              if (reception.equals("1")) {bitSet(activation_alarmes, ALARME_L);}  // Active alarm
              else {bitClear(activation_alarmes, ALARME_L);}                       
              EEPROM.write(ALARME_EEPROM, activation_alarmes); 
              }
           }                 
           
           EEPROM.commit();
           server.send ( 200, "text/csv", answer_config_probe() );   // envoi de la page  
        }

String answer_config_probe()
        {
         String page ="Configuration reussie ";
         
         return page;
      }

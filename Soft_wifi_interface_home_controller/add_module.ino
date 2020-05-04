void add_module(){


      if ( server.hasArg("ip_server") ) 
              {      
              reception=server.arg("ip_server");
              int c = reception.length() + 1;         // longueur de la chaîne de caractéres                    
              if ( c>15){ Serial.println(F("adresse ip invalide")); return;}
              reception.toCharArray(ip_server, c); 
              for (int i = 0; i < c; i++) { 
                                            EEPROM.write((i+ADRESS_SERVER),reception[i]);  // save adresse IP in EEPROM
                                            }  
              }

      if ( server.hasArg("port") ) 
              {       
              reception = server.arg("port");
              port_server=reception.toInt();           
              int b=port_server;
              for (int a=0;a<2;a++){EEPROM.write(PORT_SERVER+a ,b);b=b>>8;} // Save configuration port
              } 

      if ( server.hasArg("name") ) 
              { 
              reception=server.arg("name"); 
              int c = reception.length() + 1;         // longueur de la chaîne de caractéres                        
              if ( c>20){Serial.println(F("Nom trop long"));return;} 
              reception.toCharArray(name_module, c); 
              for (int i = 0; i < c; i++) { 
                                            EEPROM.write((i+NAME_MODULE),reception[i]);  // save adresse IP in EEPROM
                                            }  
              } 

      if ( server.hasArg("period") )       // Perios to send datas
              {       
              reception = server.arg("period");
              period=reception.toInt();           
              int b=period;
              millisecondes=period*1000;
              for (int a=0;a<2;a++){EEPROM.write(PERIOD+a ,b);b=b>>8;} 
              } 
      EEPROM.commit();     // Enregistrement

      server.send ( 200, "text/csv", answer_add_module() );   // envoi de la page  
}

/* file csv with information for php server */

String answer_add_module(){
  String page =name_module; page +=F(";");  page +=ref_module;  page +=F(";");  page +=local_mac;  page +=F(";");
         page +=local_ip; page +=F(";");  page +=version_module; page +=F("\r\n");                                      // line 1 informations module
         
         // type( probe or actuator,id,name,type_probe)

         /* DHT 22 + Ultrasonic level */
         
         page +=F("probe;p1;temp_in;DHT_22_temp\r\n");    // line 2 informations probe 1
         page +=F("probe;p2;hum_in;DHT_22_hum\r\n");      //
         page +=F("probe;p3;temp_out;BME280_temp\r\n");
         page +=F("probe;p4;hum_out;BME280_hum\r\n");
         page +=F("probe;p5;qua_in;MQ135\r\n");
         page +=F("actuator;a1;venti;VMC_3V\r\n");
         page +=F("probe;p6;tension;PZEM_4T_U\r\n");
         page +=F("probe;p7;courant;PZEM_4T_I\r\n");
         page +=F("probe;p8;puissance;PZEM_4T_P\r\n");
         page +=F("probe;p9;energie;PZEM_4T_E\r\n");
         page +=F("probe;p10;pres_out;BME280_pre\r\n");


         

         
         return page;
  }

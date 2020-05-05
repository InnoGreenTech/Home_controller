void recep_wifi(){
 if(Serial2.available()>0){
                        char a;
                        String command="";
                        String what="";
                        int  what_is;
                        String content="";
                                                
                        delay(2);                            // wait first to receive every data
                        for(int i=0;i<3;i++){
                            a=Serial2.read();
                            command +=(char)a;
                          }
                          
                        if (command!=CODE_COMMAND_INFO&&command!=CODE_COMMAND_READ&&command!=CODE_COMMAND_WRITE)
                          {
                           
                            while (Serial2.available()>0){        //read content
                            Serial2.read();}
                            Serial2.flush();
                            Serial.println("réception erronée");
                            return;
                            }

                        for(int i=0;i<2;i++){
                            a=Serial2.read();
                            what+=(char)a;
                          }
                         
                        what_is=what.toInt(); 
                        
   
                        content = "";
                        while (Serial2.available()>0 and a!='$'){        //read content
                        a=Serial2.read();
                        if (a!='$'){content += (char) a;}
                        }
                        Serial2.flush();


                  switch(what_is){         
    
                                case CODE_DATE:                               // Date actuelle
                                   date=content;       
                                   break;
                                case CODE_HEURE:                              // heure actuelle
                                   hour=content;           
                                   break;
                                case CODE_IP:                                 // adresse ip
                                   ip_address=content;           
                                   break;
                                case CODE_GATE_WAY:                           // passerelle
                                   gate_way=content;           
                                   break; 
                                case CODE_MAC:                               // adresse MAC
                                   mac_address=content;           
                                   break;                                                                                              
                                default :
                                  Serial2.flush();
                                  break;
                                }
                        
                       
                      } 
  }

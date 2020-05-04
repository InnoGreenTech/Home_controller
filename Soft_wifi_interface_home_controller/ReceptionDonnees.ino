void recep_data(){
  
 if(Serial.available()>0){
                        char a;
                        String command="";
                        String what="";
                        int  what_is;
                        String content="";
                        float float_content;
                        long   long_content;

                        delay(2);

                        for(int i=0;i<3;i++){
                            a=Serial.read();
                            command +=(char)a;
                          }
                          

                        if (command!=CODE_COMMAND_INFO&&command!=CODE_COMMAND_READ&&command!=CODE_COMMAND_WRITE)
                          {
                           
                            while (Serial.available()>0){        //read content
                            Serial.read();}
                            Serial.flush();
                            return;
                            }
                                                  
                        for(int i=0;i<2;i++){
                            a=Serial.read();
                            what +=(char)a;
                          }

                        what_is=what.toInt();        
                        content = "";

                        while (Serial.available()>0 and (char)a!='$'){        //read content
                        a=Serial.read();
                        if ((char)a!='$'){content += (char) a;}
                        }
                        long_content=content.toDouble();
                        float_content=content.toFloat();


                        switch(what_is){

          
    
                                        case CODE_TEMPERATURE_OUT:             // external temperature
                                               tOut=float_content;               
                                               break;
                          
                                        case CODE_HUMIDITY_OUT :              // external Humidity 
                                               hOut=long_content;
                                               break;

                                        case CODE_PRESSURE:
                                              pOut=long_content;
                                              break;
                                               
                                        case CODE_TEMPERATURE_IN :             // airing temperature
                                              tIn=float_content;
                                              break;
                                              
                                        case CODE_HUMIDITY_IN  :           // airing Humidity
                                              hIn=long_content;
                                              break;
                                              
                                        case CODE_CO2 :          // airing Quality
                                              qIn=long_content;
                                              break;
                                                   
                                       case CODE_SPEED_FAN :            // airing speed
                                              venti=long_content;
                                              break;
                                              

                                       case CODE_MODE :              // set summer temperature
                                              break;
                                              
                                       case CODE_SET_TEMPERATURE_SUMMER :              // Set winter temperature
                                              break;
                                              
                                       case CODE_SET_TEMPERATURE_WINTER :             // Set summer Humidity      
                                              break;
                          
                                       case CODE_SET_HUMIDITY_SUMMER :            // Set winter humidity          
                                              break;                   
                          
                                       case CODE_SET_HUMIDITY_WINTER :             // Set quality          
                                              break;                  
                          
                                       case CODE_SET_CO2 :             // Set Mode of work            
                                              break;
                          
                                       case CODE_TENSION:

                                               iU++;
                                               u=float_content; 
                                               uT=uT+u;             
                                               break;
                                               
                                       case CODE_COURANT:
                                               iI++;
                                               i=float_content;
                                               iT=iT+i;                 
                                               break;
                          
                                       case CODE_PUISSANCE:
                                               iP++;
                                               p=long_content;
                                               pT=pT+p;                    
                                               break; 
                                               
                                       case CODE_CONSOMMATION:
                                               e=long_content;                   
                                               break;                     
                                                 
                          
                                       default :
                                            break;
                                     }

                        }
}

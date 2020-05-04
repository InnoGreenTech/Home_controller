
void send_data(){

/**********************************************************
 *            Ask at RF informations                      *
 **********************************************************/


if(millis()-period_sent>PERIOD_SENT){   
                
       long  valeur[18]={(u*100),(i*100),p,e,(tOut*100),hOut,pOut,(tIn*100),hIn,qIn,venti,set_mode,(set_temperature_summer*100),(set_temperature_winter*100),set_humidity_summer,set_humidity_winter,set_co2,set_altitude} ;  
       if (index<18){            
       sent_rf(valeur[index],code[index]);          // Envoi la demande du code indexé à la radio
       }
       index++; 
       if (index==18){index=0; } // remise à zéro de l'index
        period_sent=millis();
}

/*****************************************************************************
 *                      Wait RF information to update data                   *
 *****************************************************************************/

if (radio.available()){
     
         radio.read(&trans,5);
      
         type_requiest=trans[4];                                            // lecture du byte de commande
         
         donnee= (long)trans[0]|(long)trans[1]<<8|(long)trans[2]<<16|(long)trans[3]<<24;

         Serial.print(type_requiest);Serial.print(":REPONSE:");Serial.println(donnee);

         Serial2.print(CODE_COMMAND_INFO);

         switch(type_requiest){

          
    
              case CODE_TEMPERATURE_OUT:             // external temperature
                     tOut=float(donnee)/100;
                     Serial2.print(type_requiest);Serial2.println(tOut);  // Sent the values at wifi module                     
                     break;

              case CODE_HUMIDITY_OUT :              // external Humidity 
                     hOut=donnee;
                     Serial2.print(type_requiest);Serial2.println(hOut);  // Sent the values at wifi module
                     break;
                     
              case CODE_TEMPERATURE_IN :             // airing temperature
                    tIn=float(donnee)/100;
                    Serial2.print(type_requiest);Serial2.println(tIn);  // Sent the values at wifi module
                    break;
                    
              case CODE_HUMIDITY_IN :           // airing Humidity
                    hIn=donnee;
                    Serial2.print(type_requiest);Serial2.println(hIn);  // Sent the values at wifi module
                    break;
                    
              case CODE_CO2 :          // airing Quality  
                    qIn= donnee;
                    Serial2.print(type_requiest);Serial2.println(qIn);  // Sent the values at wifi module
                    break;
                         
             case CODE_SPEED_FAN :            // airing speed
                    venti=donnee;
                    Serial2.print(type_requiest);Serial2.println(venti);  // Sent the values at wifi module
                    break;

             case CODE_PRESSURE:
                    pOut= donnee * pow((1 - ((0.0065 * set_altitude) / (tOut + 0.0065 * set_altitude + 273.15))), -5.257);
                    Serial2.print(type_requiest);Serial2.println(pOut);  // Sent the values at wifi module
                    break;
                    
                   
             case CODE_SET_TEMPERATURE_SUMMER:              // set summer temperature
                    break;
                    
             case CODE_SET_TEMPERATURE_WINTER :              // Set winter temperature
                    break;
                    
             case CODE_SET_HUMIDITY_SUMMER :             // Set summer Humidity      
                    break;

             case CODE_SET_HUMIDITY_WINTER :            // Set winter humidity          
                    break;                   
   
             case CODE_MODE :             // Set Mode of work            
                    break;

             case CODE_TENSION:
                     u=float(donnee)/100;
                     Serial2.print(type_requiest);Serial2.println(u);  // Sent the values at wifi module                     
                     break;
                     
             case CODE_COURANT:
                     i=float(donnee)/100;
                     Serial2.print(type_requiest);Serial2.println(i);  // Sent the values at wifi module                     
                     break;

             case CODE_PUISSANCE:
                     p=donnee;
                    Serial2.print(type_requiest);Serial2.println(p);  // Sent the values at wifi module                     
                     break; 
                     
             case CODE_CONSOMMATION:
                     e=donnee;
                     Serial2.print(type_requiest);Serial2.println(e);  // Sent the values at wifi module                     
                     break;                     
                       

             default :
                  break;
         }
}
      
  
}

void sent_rf(long information,byte commande){

         radio.stopListening(); //Arrêt de l'écoute
         
         
         radio.flush_tx();
     
         trans[0]=information;        // Lecture du bit faible
         trans[1]=information>>8;     
         trans[2]=information>>16;       
         trans[3]=information>>24;     
         
         trans[4]=commande;           // Indique que l'on demande d'envoyer les données lues.
         
         radio.write(&trans,5,1); 
      
 
         radio.startListening(); // Mise en écoute du module radio

         

}

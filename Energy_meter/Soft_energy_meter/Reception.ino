 void recep(){



if (radio.available()){

         long information;
         
         radio.read(&trans,5);

    
         nature=trans[4];                                            // lecture du byte de commande
         
 
         donnee= (long)trans[0]|(long)trans[1]<<8|(long)trans[2]<<16|(long)trans[3]<<24;

        
         switch(nature){
             
              case CODE_TENSION:             // Tension  
                     information=v*100;       // transform in long
                     envoi(information,CODE_TENSION);
                     break;

              case CODE_COURANT:             // Courant
                     information=i*100;      // transform in long
                     envoi(information,CODE_COURANT);
                     break;              

              case CODE_PUISSANCE:             // Puissance
                     information=p;
                     envoi(information,CODE_PUISSANCE);
                     break; 
                     
              case CODE_CONSOMMATION:             // Energie
                     information=e;
                     envoi(information,CODE_CONSOMMATION);
                     break;                      
         }
        
        }


}

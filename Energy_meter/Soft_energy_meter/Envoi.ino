 void envoi(float information,byte commande){

       // Envoi des données  
  
        radio.stopListening(); //Arrêt de l'écoute
        radio.flush_tx();

        donnee=information;

     
         trans[0]=donnee;        // Lecture du bit faible
         trans[1]=donnee>>8;     
         trans[2]=donnee>>16;       
         trans[3]=donnee>>24;     
         
         trans[4]=commande;           // Indique que l'on demande d'envoyer les données lues.
         
        radio.write(&trans,5,1);

     //   delayMicroseconds(250);
     
        radio.startListening(); // Mise en écoute du module radio

     

} 

void envoi(long information,byte commande){
  
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

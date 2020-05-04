void rf_request(long information,byte commande){

         radio.stopListening();          
         
         radio.flush_tx();
     
         trans[0]=information;         // transform word information
         trans[1]=information>>8;     
         trans[2]=information>>16;       
         trans[3]=information>>24;     
         
         trans[4]=commande;           //Type of request
         radio.write(&trans,5,1); 
      
 
         radio.startListening();      // return in listen mode

         

}

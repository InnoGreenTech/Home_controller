void get_sensors(){
  


  


  if (millis()-aquisition>2000) // si derniére aquisition date de deux secondes
  
  { 

    

    
     tIn= dht_in.readTemperature(); //lecture de la température en °
     //Serial.println(tIn);
     hIn= dht_in.readHumidity(); // Lecture de l'humidité

     tOut=bme_out.readTempC();
     

     pOut=bme_out.readFloatPressure()/100;

     //Serial.println(pOut);
     
     hOut=bme_out.readFloatHumidity();

     qIn=read_co2();

        
     aquisition=millis();
  }
  
}

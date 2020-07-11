void send_data(){

    
    if ( WiFi.status()!= WL_CONNECTED)
    
        {
        if (nb_cycle_lost_wifi<NB_TRYING_CONNECT)                            // test the wifi connection  if lost it, reset the module
                      {
                      nb_cycle_lost_wifi++;
                      lastmessage = lastmessage+30000;
                      return;              
                      } 

        else {ESP.reset();}  // if the lost of wifi
        }

      String ip=WiFi.localIP().toString().c_str();
      String data;
      /* Création des données json */

      
       
     const size_t bufferSize =JSON_OBJECT_SIZE(15);
     DynamicJsonDocument root(bufferSize);
     
     root["mac_adress"]=WiFi.macAddress();
     root["ip_adress"]=ip; 
     root["p1"] =  tIn;
     root["p2"] =  hIn;
     root["p3"]=   tOut;
     root["p4"]=   hOut;
     root["p5"]=   qIn;
     root["a1"]=   venti;
     if(iU==0){root["p6"]=0;}
     else{root["p6"]=   uT/iU;}      // Envoi de la moyenne entre deux envois
     if(iI==0){root["p7"]=0;}
     else{root["p7"]=   iT/iI;}
     if(iP==0){root["p8"]=0;}
     else{root["p8"]=   pT/iP;}
     root["p9"]=   e;
                              
     serializeJson(root,data);   
     String adresse="http://";
     adresse+=ip_server;
     adresse+="/InnoGreenTech/controller/json_probe.php";
     String data1= "data=";
     data1 +=data;
     //Serial.println(data1);

     HTTPClient http;
     int httpCode = 0;
     http.begin(adresse);
     http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //http.addHeader("Content-Type", "application/json");
     httpCode = http.POST(data1);
     String payload = http.getString();
     //Serial.println(httpCode);   //Print HTTP return code
     //Serial.println(payload);
     http.end();  //Close connection
     
     iT=0;
     iI=0;
     uT=0;
     iU=0;
     pT=0;
     iP=0;
 
     nb_cycle_lost_wifi=0;
                 //     compteurLast=1;      
     lastmessage= millis();

             
      
  
}

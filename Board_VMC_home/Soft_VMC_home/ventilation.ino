void fan_control(){


  

 // Régulation de la vitesse en fonction de la qualité

  switch(vq){

             case 1:
                if(qIn>set_co2){vq=2;}
                break;
        
             case 2:
                if(qIn<set_co2*0.8){vq=1;}
                if(qIn>set_co2*1.2){vq=3;}
                break;
        
             case 3:
                if(qIn<set_co2){vq=2;}
                break;
  
             default :
                  vq=1;
                  break;
            } 
        
        


//Régulation en fonction de l'humidité



      // Calcul  de l'humidité extérieur ramener à la température intérieur:
     float hCourbe;  // Humidité calculer par la courbe de saturation pour une contenance d'eau de 5g/M3
     float fCourbe;  // Ratio calculer  pour la charge réelle d'eau
     float hTin;     // Taux d'humidité ramener à la température intérieur

     
     hCourbe=1+(100/exp(tOut/16));            // Calcul du point de mesure
     fCourbe=hOut/hCourbe;                    // Calcul du facteur 
     hTin=(1+(100/exp(tIn/16)))*fCourbe;      // Calcul du facteur 




      if (hIn>hTin)    // régulation de l'humidité si l'humidité extérieur est inférieur
      {
        if (hIn<(set_humidity_winter*1.1)){ vh=1;}                      // Ventilation à 1 si l'humidité est proche de la consigne
        if (hIn>(set_humidity_winter*1.15)&& hIn<(set_humidity_winter*1.25)){vh=2;}     // Est supérieur de 10 %
        if (hIn>(set_humidity_winter*1.3)){vh=3;}// Ventilation à 3     // Est supérieur de 30 %
       }
   
     else { vh=1;} // Si humidité extérieur élévée  alors consigne à 1
   //      if (hIn<hOut)   // régulation de l'humidité si l'humidité extérieur est supérieur à l'intérieur
   //     {
   //      if (hIn>(set_humidity_winter-4)){ vh=1;}     // Ventilation à 1 si l'humidité est proche de la consigne
   //      if (hIn<(set_humidity_winter-5)&& hIn>(hhc-9)){vh=2;}                // Ventilation en mode médium
   //      if (hIn<(set_humidity_winter-10)){vh=3;}// Ventilation à 3
   //   }
  

  




  

  // Gestion de la ventilation du mode Hivers
  
  
    if (set_mode==1) // ventilation en mode Hivers  ( optimisation  de l'énergie)
     {
     
     if (tIn>tOut) // Si la température extérieur est inférieure
         {
         if (tIn<(set_temperature_winter*1.10)){vt=1;};
         if (tIn>(set_temperature_winter*1.15) && tIn<(set_temperature_winter*1.2)){vt=2;}  // Ventilation à 2 en cas de chauffe trop importante
         if (tIn>(set_temperature_winter*1.25)){vt=3;}                   // Ventilation maximum pour surchauffe              
         }
         
     if (tIn<=tOut)        // Si la température extérieur est supérieur
         {
         if (tIn<(set_temperature_winter*1.05)){vt=3;}; // on ne sait jamais si l'on peut récupérer un peu de chaleur
         if (tIn>(set_temperature_winter*1.10)){vt=1;}  // Ventilation à 1
        
         }     
      }

    // Gestion de la ventilation du mode Eté
  
  
      if (set_mode==2)
      {
      if (tIn>tOut) // Si la température extérieur est inférieure
         {
         if (tIn<(set_temperature_summer*0.9)){vt=1;};
         if (tIn>set_temperature_summer){vt=3;}  // Ventilation à 3 pour refroidir
            
         }
         
      if (tIn<=tOut)        // Si la température extérieur est supérieur
         {vt=1;}
       }

  

// mise à jour des sorties

   if (vq==3||vt==3||vh==3) {venti=3;} 
   else if (vq==2||vt==2||vh==2) {venti=2;}
   else {venti=1;}
   
// mode manuel 

    if (set_mode==0){venti=0;} // Ventilation arrêtée
    if (set_mode==4){venti=1;} // Mode forcée à 1
    if (set_mode==5){venti=2;} //Mode Forcée à 2
    if (set_mode==6){venti=3;} //Mode Forcée à 3
//    if (venti==0 && set_mode>0){venti=1;}// Forçage à 1 de la ventilation si changement de mode
   if (venti_last!=venti){
       if (venti==0){digitalWrite(R1,LOW);digitalWrite(R2,LOW);digitalWrite(R3,LOW);} // arrêt ventilation
       if (venti==1){digitalWrite(R2,LOW);digitalWrite(R3,LOW);delay (1000);digitalWrite(R1,HIGH);} // Vitesse 1
       if (venti==2){digitalWrite(R1,LOW);digitalWrite(R3,LOW);delay (1000);digitalWrite(R2,HIGH);} // Vitesse 2
       if (venti==3){digitalWrite(R1,LOW);digitalWrite(R2,LOW);delay (1000);digitalWrite(R3,HIGH);} // Vitesse 3
   }

   venti_last=venti;
  }

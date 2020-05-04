/* current and forecasts weather, use out door imformation */

void weather(){

  /* creat a houre arrow to forecasts_weather */

  if (current_sample_pressure<total_samples_pressure){current_sample_pressure++;current_average_pressure=current_average_pressure+(qIn/total_samples_pressure);}
  else{
    rotate_index++;
    if (rotate_index>NUMBER_SAMPLES_HOUR){rotate_index=0;}
    average_pressure[rotate_index]= current_average_pressure;
    current_average_pressure=0;
    current_sample_pressure=0; 
  } 
    
  float current_p=average_pressure[rotate_index]; 
  float last_hour_p;
  

  if(rotate_index+1<NUMBER_SAMPLES_HOUR){last_hour_p = average_pressure [rotate_index+1];}
  else {last_hour_p = average_pressure [0];}

  // current Weather

  if (current_p<1006){current_weather=RAIN;}
  else if (current_p<1020){current_weather=CLOUDLY;}
  else {current_weather=SUNNY;}

  float dp= last_hour_p-current_p;

  if (-0.25<dp>0.25){forecasts_weather=current_weather;}
  
  if (dp>=1 and current_p<1006 ){forecasts_weather=CLOUDLY;}
  else if (dp>=0.25){forecasts_weather=SUNNY;}
  
  if(dp<=-0.25 and current_p>1020){forecasts_weather=CLOUDLY;}
  else if(dp<=-0.25){forecasts_weather=RAIN;}
  else if(dp<=-1){forecasts_weather=THUNDERSTORM;}  
  }

void wamp_info(){
              if ( server.hasArg("temp_salon")) 
              {      
                String decodage=server.arg("PASSWORD");
                tsalon= decodage.toFloat();
                send_data();
              } 
                }

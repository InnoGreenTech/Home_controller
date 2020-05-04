
void indexRoot(){
              if ( server.hasArg("envoi")) 
              {      
                send_data();
              } 
               server.send ( 200, "text/html", indexPage() );   // envoi de la page
                }
  




String indexPage(){
                          String page =F("<!DOCTYPE html> <html lang=fr-FR><head><meta charset='utf-8'><link rel='stylesheet'type='text/css'href='style.css'><title>Solar Greenhouse</title></head>");
                                 page +=F("<body>");
                                 page +=F("<nav> <ul id='menu'><li><a href='index.html'> Accueil </a></li><li><a href='firmware'> Update </a></li</ul></nav>");
                                
                                 page +=F("<div id='page'>");
                                 
                                 page +=F("<header><h1>Centrale maison</h1></header>");

                                 page +=F("<div id='corp'>");
                                 page +=F("<section id='datedujour'><h2>");
                                 page +=NTP.getDateStr();
                                 page +=F("</h2><h3>");
                                 page +=NTP.getTimeStr();
                                 page +=F("</h3>");
                                 page +=F("<Table><tr><td>Serveur:</td><td></td><td>");
                                 page +=ip_server;
                                 page +=F("</td></tr><tr><td>Port serveur:</td><td></td><td>");
                                 page +=port_server;
                                 page +=F("</td></tr><tr><td>Adresse MAC:</td><td></td><td>");
                                 page +=local_mac;
                                 page +=F("</td></tr><tr><td>Version:</td><td></td><td>");
                                 page +=version_module;
                                 page +=F("</td></tr></tr></Table></section>");
      
                                 page +=F("<section id='outdoor'><h2> Capteur extérieur </h2><ul><li>Température: ");
                                 page +=tOut;
                                 page +=F(" °c</li><li> Humidité:");
                                 page +=hOut;
                                 page +=F(" %</li><li> Pression atmosphérique:");
                                 page +=int(pOut);
                                 page +=F(" mb</li></ul></section>");
      
                                 
                                 page +=F("<section id='indoor'><h2> Capteur Intérieur </h2><ul><li>Température: ");
                                 page +=tIn;
                                 page +=F(" °c</li><li> Humidité: ");
                                 page +=hIn;
                                 page +=F(" %</li><li> CO2: ");
                                 page +=qIn;
                                 page +=F(" ppm</li><li> Ventilation: ");
                                 page +=venti;
                                 page +=F(" </li></ul></section>");
                           
                                 page +=F("<section id='energie'><h2> Compteur d'énergie  </h2><ul><li>Tension: ");
                                 page +=u;
                                 page +=F(" Volts</li><li>Courant: ");
                                 page +=i;
                                 page +=F(" Ampéres</li><li>Puissance: ");
                                 page +=p;
                                 page +=F(" Watts</li><li>Energie Consommée: ");
                                 page +=e/1000;                           
                                 page +=F("  kWh</li></ul></section>");

                                 page +=F("<section id='sent'><h2> Envoi données  </h2><ul><li>Périodicité actuelle ");
                                 page +=period;
                                 page +=F(" secondes</li><li><form method='get'><input type='hidden' name='envoi' value='1'/><input type='submit' value='envoi'/>");                      
                                 page +=F("</form></li></ul></section>");
                                 
                                 page +=F("</div>");
                           
                           page +=F("<footer><table><tr><td><a href='http://innogreentech.fr'>InnoGreenTech  </a></td><td></td><td><a href='mailto: info@innogreentech.fr'> Contactez moi</a></td></tr></table></footer>");
                           page +=F("</body></html>");                 
                           return page;
                          }

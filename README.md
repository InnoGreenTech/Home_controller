# Home_controller
Home controller allow to pilote the VMC.  For this it reads the CO2, Humidity and temperature. It is able also forecast the Weather. It have a touch screen.

Description:
------------

Home controller allow to pilote a VMC. It use a MH-Z19B sensor to measure the C02 and DHT22 for humidity and temperature in the pipe of the ventilation.
A BME280 allow to measure humidity, temperature and pressure in out door, like this is possible to forecaste weather.

There are a main card with a touch screen and a remote VMC.

Also ther is another modul to measure the power consomation of the house. Is it possible to read them in real time.

A optional ESP8266, allow to sent data with a Json file and it is possible to connect at a webpage with evry information.


[*You can found more information on my web site on this page*](https://innogreentech.fr/fr/objets-connectes/mesures/70-controleur-de-vmc)


I share also the drawing, the pcb, and the box designe in this repository.


Screen interface:
----------------
![Picture of current status](https://innogreentech.fr/images/Photos/Gestionnaire%20maison/screen_one.jpg)

Remote VMC:
----------------

![Picture of current status](https://innogreentech.fr/images/Photos/Gestionnaire%20maison/remote_vmc.JPG)

Remote energie meter:
----------------

![Picture of current status](https://innogreentech.fr/images/Photos/Mesure%20de%20puissance/compteur.png)



Contributing:
-------------

Fork it.
Create your feature branch (git checkout -b my-new-feature).
Commit your changes (git commit -am 'Add some feature').
Push to the branch (git push origin my-new-feature).
Create new Pull Request.

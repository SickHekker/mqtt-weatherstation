# MQTT-Weatherstation
A basic solar powered weatherstation that provides temperature, humidity and pressure.

Make sure to set up MQTT with SSL in your Mosquitto broker.

My setup pushes the data on the MQTT feed to InfluxDB using Node-RED.
From there i can visualise this data with Grafana or Node-RED.

# Parts
You can order all of these parts from Aliexpress.  
I recommend to get a 18650 battery from a reputable seller. (like Conrad, Farnell & etc)  
If you buy a battery from a place like Aliexpress you might run into problems with shipping because its a battery.  
Also because you will likely get a higher quality battery with accurate advertised capacity.  

Wemos D1 mini  
BME1280 (i2c)  
TP4056 board (The version with only 4 terminals is easier to solder)  
18650 LiPo Battery  
18650 Battery holder  
5.5V 0.66W Solar panel  
Some wire terminals  
Some female pin headers  
Some male pin headers  
Some breadboard female to female wires for the BME280  
Protoboard  

# Libraries
BME280: https://github.com/finitespace/BME280
MQTT: https://github.com/adafruit/Adafruit_MQTT_Library  

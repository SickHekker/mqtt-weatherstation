# MQTT-Weatherstation

Code for the Solar Powered basic weatherstation

Make sure to set up MQTT with SSL in your Mosquitto broker.

My setup pushes the data on the MQTT feed to InfluxDB using Node-RED.
From there i can visualise this data with Grafana or Node-RED.

<h1>Parts</h1>
Wemos D1 mini
BME280 (i2c)
TP4056 board (The version with only 4 terminals is easier to solder)
18650 Battery
18650 Battery holder
5.5V 0.66W Solar panel
Some wire terminals
Some female pin headers
Some male pin headers
Some breadboard female to female wires for the BME280
Protoboard

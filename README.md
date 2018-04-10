# mqtt-weatherstation
Code for the Solar Powered basic weatherstation

Make sure to set up MQTT with SSL in your Mosquitto broker.

My setup pushes the data on the MQTT feed to InfluxDB using Node-RED.
From there i can visualise this data with Grafana or Node-RED.

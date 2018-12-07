#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Wire.h>
#include <BME280I2C.h>

#define SEALEVELPRESSURE_HPA (1013.25)

// Deepsleep duration in seconds.
int sleep = 300;

// Set the MQTT feeds to be used
#define temperature_feed "/outdoor/sensors/weatherstation/bme280/temperature"
#define humidity_feed "/outdoor/sensors/weatherstation/bme280/humidity"
#define pressure_feed "/outdoor/sensors/weatherstation/bme280/pressure"

/************************* WiFi Access Point *********************************/

WiFiClientSecure client;
#define WLAN_SSID "wifissid"
#define WLAN_PASS "wifipassword"

/************************* MQTT Broker Setup *********************************/

#define AIO_SERVER      "mqttserver"
#define AIO_SERVERPORT  8883                   // 8883 for MQTTS
#define AIO_USERNAME    "mqttusername"
#define AIO_KEY         "mqttpassword"

/****************************** Feeds ***************************************/

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish temperature_topic = Adafruit_MQTT_Publish(&mqtt, temperature_feed);
Adafruit_MQTT_Publish pressure_topic = Adafruit_MQTT_Publish(&mqtt, pressure_feed);
Adafruit_MQTT_Publish humidity_topic = Adafruit_MQTT_Publish(&mqtt, humidity_feed);

/*************************** Sketch Code ************************************/

BME280I2C bme;

void setup() {
  Serial.begin(115200);
  delay(10);
  
  int wifitry = 20;
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  delay(250);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    wifitry++;
    if (wifitry >= 50) {
      Serial.println("Can't connect to WiFi, activating deepsleep");
      wifitry = 0;
      ESP.deepSleep(sleep * 1000000);
    }
  }

  Wire.begin();

  delay(10);

  if (!bme.begin()) {
    Serial.println("Can't find the BME280 sensor, activating deepsleep");
    ESP.deepSleep(sleep * 1000000);
  }
  
  MQTT_connect();

  float temperature(NAN), humidity(NAN), pressure(NAN);
  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_hPa);
  
  bme.read(pressure, temperature, humidity);
 
  delay(100);
  
  Serial.println(temperature);
  Serial.println(humidity);
  Serial.println(pressure);
  
  delay(100);
  
  temperature_topic.publish(temperature);
  humidity_topic.publish(humidity);
  pressure_topic.publish(pressure);
    
  Serial.println("Data posted to MQTT");
  mqtt.disconnect();
  Serial.println("MQTT disconnected, activating deepsleep");
  ESP.deepSleep(sleep * 1000000);
  
}

void loop() {
  ESP.deepSleep(sleep * 1000000);
}

void MQTT_connect() {
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 5;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 1 second...");
    mqtt.disconnect();
    delay(500);  // wait a half second
    retries--;
    if (retries == 0) {
      ESP.deepSleep(sleep * 1000000);
    }
  }
  
  Serial.println("MQTT Connected!");
}

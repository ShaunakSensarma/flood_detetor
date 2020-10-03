//Real Time Flood monitoring system
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <IFTTTWebhook.h>
#define pot_pin A0;

#define FIREBASE_HOST "flood-detection.firebaseio.com"
int threshold_phaseone=400;
int threshold_phasetwo=800;
int threshold_phasethree=1050;
#define your_url "http://maker.ifttt.com/trigger/flood_detection/with/key/cGM9Nd9B2dUhiCcEXr0Y3P3SAhCLPFS-hg0ljrwg_3X"
#define ssid "R K S"
#define pass "abcd#1234"
IFTTTWebhook webhook("cGM9Nd9B2dUhiCcEXr0Y3P3SAhCLPFS-hg0ljrwg_3X","flood_detection","9A:11:97:AD:CD:4F:D9:DF:E4:8F:1B:01:5F:4F:69:D3:87:EA:D9:4B");


void setup() {

   Serial.begin(9600);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST);
  
}

void loop() {
  int sensorValue=analogRead(A0);
  if(sensorValue>threshold_phaseone&&sensorValue<threshold_phasetwo)
  {
  Serial.println("Critical phase one value");
  Serial.println("Sending Message");
  Serial.println(sensorValue);
  Firebase.setFloat ("Flood_sensor_value",sensorValue);
  webhook.trigger();
  delay(2000);
  Serial.println("Message Sent");
  }
}

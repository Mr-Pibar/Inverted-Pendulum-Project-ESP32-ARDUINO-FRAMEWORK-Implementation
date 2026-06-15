#include <connectivity.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <wifiAndMQTT.h>
#include <Arduino.h>

const char* ssid = "B3NGZ ORBIT";
const char* wifi_pass = "Petemambu2025!";

//mqtt
const char* mqtt_server = "armadillo.rmq.cloudamqp.com";
const int   mqtt_port   = 1883;

const char* mqtt_user = "ylhrbnlm:ylhrbnlm";
const char* mqtt_pass = "hWqFR1OZ3PkzfIWUHVdQi-GHVmLMnsll";

const char* topic_pot0 = "DATA_LINE_0";

WiFiClient ESP_WIFI;
PubSubClient client(ESP_WIFI);

volatile unsigned int step_mqtt = 0;
volatile unsigned int dir_mqtt = 1;

void initWifi(){
   Serial.println("\nCONNECTING WIFI...");
   WiFi.begin(ssid, wifi_pass);

   while(WiFi.status() != WL_CONNECTED){
    delay(250);
    Serial.print(".");
   }

   Serial.println();
   Serial.println("WIFI CONNECTED");
   Serial.print("[IP] ");
   Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length){
    String mqtt_data;
    unsigned int i;

    for(i = 0; i < length; ++i){
        mqtt_data += (char)payload[i];
    }

    int comma_index = mqtt_data.indexOf(',');
    if(comma_index == -1){
        Serial.println("INVALID MQTT (FORMAT)");
        return;
    }
    String step_string = mqtt_data.substring(0, comma_index);
    String dir_string = mqtt_data.substring(comma_index +1);

    step_mqtt = step_string.toInt();
    if(dir_string == "CW"){
        dir_mqtt = 1;
    }
    else if(dir_string == "CCW"){
        dir_mqtt = 0;
    }
    else{
        Serial.println("INVALID MQTT (DIRECTION)");
        return;
    }

    Serial.println("=============================");
    Serial.print("TOPIC : ");
    Serial.println(topic);
    Serial.print("STEP DATA :");
    Serial.println(step_mqtt);
    Serial.print("DIR DATA :");
    Serial.println(dir_mqtt);
    Serial.println("=============================");
}

void initMQTT(){
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void reconnectMQTT(){
    while(!client.connected()){
        Serial.println("CONNECTING MQTT...");
        if(client.connect("ESP32Client", mqtt_user, mqtt_pass)){
            Serial.println("MQTT CONNECTED");
            client.subscribe(topic_pot0);
        }
        else{
            Serial.print("FAIL: ");
            Serial.println(client.state());
            delay(1000);
        }
    }
}

void updateMQTT(){
    client.loop();
}
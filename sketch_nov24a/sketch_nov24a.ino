#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// GPIO 5 D1
#define LED 5
// WiFi
const char *ssid = "Mi 10"; // Enter your WiFi name
const char *password = "bisheng1579";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "8.141.146.255";
const char *topic = "AGG";
const char *mqtt_username = "BS";
const char *mqtt_password = "123456";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    // Set software serial baud to 115200;
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    // connecting to a WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp8266-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Public emqx mqtt broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    // publish and subscribe
    client.publish(topic, "hello emqx");
    client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    String message;
    for (int i = 0; i < length; i++) {
        message = message + (char) payload[i];  // convert *byte to string
    }
    Serial.print(message);
    if (message == "off") { digitalWrite(LED, LOW); }   // LED on
    if (message == "on") { digitalWrite(LED, HIGH); } // LED off
    Serial.println();
    Serial.println("-----------------------");
}

void loop() {
    client.loop();
}

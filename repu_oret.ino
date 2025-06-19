
//=====================================================================ini mqtt =================================
/*
#include <ESP8266WiFi.h>
#include <PubSubClient.h>   //ini bisa membloking wifi sebaiknya gunakan asynmqtt  

// WiFi
const char *ssid = "MY REPUBLIC"; // Enter your WiFi name
const char *password = "12345678"; // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "balamantra";
const char *mqtt_username = "memet";
const char *mqtt_password = "bungapala";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Set software serial baud to 115200;
  Serial.begin(115200);
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
    String client_id = "memet";
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
  client.publish(topic, "balamantra");
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

void loop() {
  client.loop();
}

*/

//=====================================================================ini email=================================
/*
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

const char* ap_ssid = "ESP8266_AP";
const char* ap_password = "12345678";

ESP8266WebServer server(80);

String ssid;
String password;

void handleRoot() {
    String html = "<html><body>"
                  "<h1>ESP8266 WiFi Config</h1>"
                  "<form action=\"/save\" method=\"POST\">"
                  "SSID: <input type=\"text\" name=\"ssid\"><br>"
                  "Password: <input type=\"password\" name=\"password\"><br>"
                  "<input type=\"submit\" value=\"Save\">"
                  "</form>"
                  "</body></html>";
    server.send(200, "text/html", html);
}

void handleSave() {
    if (server.hasArg("ssid") && server.hasArg("password")) {
        ssid = server.arg("ssid");
        password = server.arg("password");

        EEPROM.begin(512);
        EEPROM.write(0, ssid.length());
        for (int i = 0; i < ssid.length(); ++i) {
            EEPROM.write(1 + i, ssid[i]);
        }
        EEPROM.write(1 + ssid.length(), password.length());
        for (int i = 0; i < password.length(); ++i) {
            EEPROM.write(2 + ssid.length() + i, password[i]);
        }
        EEPROM.commit();

        server.send(200, "text/html", "<html><body><h1>Saved! Rebooting...</h1></body></html>");
        delay(3000);
        ESP.restart();
    } else {
        server.send(400, "text/html", "<html><body><h1>Invalid request</h1></body></html>");
    }
}

void setup() {
    Serial.begin(115200);
    EEPROM.begin(512);

    int ssidLength = EEPROM.read(0);
    ssid = "";
    for (int i = 0; i < ssidLength; ++i) {
        ssid += char(EEPROM.read(1 + i));
    }
    int passwordLength = EEPROM.read(1 + ssidLength);
    password = "";
    for (int i = 0; i < passwordLength; ++i) {
        password += char(EEPROM.read(2 + ssidLength + i));
    }

    if (ssid.length() > 0 && password.length() > 0) {
        WiFi.begin(ssid.c_str(), password.c_str());
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("Connected to WiFi");
    } else {
        WiFi.softAP(ap_ssid, ap_password);
        Serial.println("Started Access Point");
    }

    server.on("/", handleRoot);
    server.on("/save", HTTP_POST, handleSave);
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}

*/

/*
Gmail SMTP Server Settings
If you’re using a Gmail account, these are the SMTP Server details:

SMTP Server: smtp.gmail.com
SMTP username: Complete Gmail address
SMTP password: Your Gmail password
SMTP port (TLS): 587
SMTP port (SSL): 465
SMTP TLS/SSL required: yes


wpup bjah iddi wyhp
*/

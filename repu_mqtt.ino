

void connectToWifi(){
//  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to ");
  Serial.println(ssid);
}


void connectToMqtt(){
  Serial.println("menghubungkan ke mqtt ");
  mqttClient.connect();
}


void jalankanMqtt(){
  
  // Setup WiFi event handlers
  WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP& event) {
    Serial.print("Connected to WiFi. IP: ");
    Serial.println(WiFi.localIP());
    connectToMqtt();
  });
  
  WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected& event) {
    Serial.println("WiFi disconnected. Attempting reconnect...");
    mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
    wifiReconnectTimer.once(2, connectToWifi);
    
  });

  // Setup MQTT client
  mqttClient.onConnect([](bool sessionPresent) {
    Serial.println("Connected to MQTT broker");
    mqttClient.subscribe(mqtt_topic_sub, 1);
  });
  
  mqttClient.onDisconnect([](AsyncMqttClientDisconnectReason reason) {
    Serial.println("Disconnected from MQTT broker");
    if (WiFi.isConnected()) {
      mqttReconnectTimer.once(2, connectToMqtt);
    }
  });

   mqttClient.onMessage([](char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
    // Handle incoming MQTT messages
    String message;
    for (size_t i = 0; i < len; i++) {
      message += (char)payload[i];
    }
    Serial.println(message);
    
//    if (String(topic) == mqtt_topic_sub) {
//      if (message == "ON") {
//        ledState = true;
//        digitalWrite(LED_BUILTIN, LOW);
//      } else if (message == "OFF") {
//        ledState = false;
//        digitalWrite(LED_BUILTIN, HIGH);
//      }
//    }
  });
  
  
  
}

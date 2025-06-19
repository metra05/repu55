
String scanDulu(){
  int n = WiFi.scanNetworks();
    String json = "[";
    for (int i = 0; i < n; ++i) {
      if (i > 0) json += ",";
      json += "{\"ssid\":\"" + WiFi.SSID(i) + "\",\"rssi\":" + String(WiFi.RSSI(i)) + "}";
    }
    json += "]";
    return json;
}


String hasil() {
  String html = "tes";

  // Lakukan scan jaringan
    int n = WiFi.scanNetworks();
    
    String json = "[";
    for (int i = 0; i < n; ++i) {
      if (i > 0) json += ",";
      
      byte* mac = WiFi.BSSID(i);
      char macStr[18];
      snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", 
               mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      
      json += "{";
      json += "\"ssid\":\"" + WiFi.SSID(i) + "\",";
      json += "\"rssi\":" + String(WiFi.RSSI(i)) + ",";
      json += "\"channel\":" + String(WiFi.channel(i)) + ",";
      json += "\"encryption\":" + String(WiFi.encryptionType(i) != ENC_TYPE_NONE) + ",";
      json += "\"mac\":\"" + String(macStr) + "\"";
      json += "}";
    }
    json += "]";
  Serial.println(html);

  return String(html);
  //server.send(200, "text/html", json);
}

String encryptionTypeToString(uint8_t type) {
  switch(type) {
    case ENC_TYPE_WEP: return "WEP";
    case ENC_TYPE_TKIP: return "WPA/PSK";
    case ENC_TYPE_CCMP: return "WPA2/PSK";
    case ENC_TYPE_NONE: return "Open";
    case ENC_TYPE_AUTO: return "Auto";
    default: return "Unknown";
  }
}

String getTime() {
  // Fungsi sederhana untuk mendapatkan waktu saat ini
  // Di aplikasi nyata, Anda mungkin ingin menggunakan RTC atau NTP
  return String(millis() / 1000) + " detik setelah startup";
}

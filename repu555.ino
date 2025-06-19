
// Import required libraries //data uploaddata tidak menggunakan littlefs tapi spiffs
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>

#include <ESP_Mail_Client.h>
#include <AsyncMqttClient.h> //<PubSubClient.h> //awas pakai ini ngeblock async webserver
#include <Ticker.h>

#include <Wire.h>
#include "Sodaq_DS3231.h"
#include <EmSevenSegment.h>
#include <EEPROM.h>

//ini variable punyanya email notification
/** The smtp host name e.g. smtp.gmail.com for GMail or smtp.office365.com for Outlook or smtp.mail.yahoo.com */
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

/* The sign in credentials */
#define AUTHOR_EMAIL "metra05@gmail.com"
#define AUTHOR_PASSWORD "wpuw bjah iddi wyhp"  //ini app password bukan akun password

/* Recipient's email*/
#define RECIPIENT_EMAIL "metra05@gmail.com"  //dearjuwariyah@gmail.com"  //awas error exception(29) pada penggunaan library esp email client
                                                                         //jika alamat email yang dituju salah, khususunya saat ic baru
/* Declare the global used SMTPSession object for SMTP transport */
SMTPSession smtp;

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status);

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
//const char *topic = "balamantra";
const char *mqtt_username = "memet";
const char *mqtt_password = "bungapala";
const int mqtt_port = 1883;
const char *mqtt_topic_pub = "balamantra";
const char *mqtt_topic_sub = "balamantra";


EmSevenSegment disp(4, 'A', 12, 14, 13);      //data clock strobe   12 13 14

char weekDay[][7] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};
byte ahr[7], pilhar[7], pilhar1[7], pilhar2[7], pilhar3[7], pilhar4[7]; //untuk alarm buzer
byte pilharh[7], pilhar1h[7];  //untuk alarm relay harian

// Replace with your network credentials
const char* ap_ssid = "ESP8266_AP_ruwet2";
const char* ap_password = "12345678";

String ssid;
String password;
String tes;

//const char* ssid = "MY REPUBLIC";  //Wifi_Gratis";
//const char* password = "12345678";

// Set LED GPIO
//const int ledPin = 2;
const int kedip = 16;
const int BUZZ = 0;     //ingat gpio0 harus kondisi high saat boot!!!!! hati hati memihlih pin
const int rel = 2;   //ini dipakai oleh relay pnp
const int RESET_BUTTON_PIN = 15; // 12; 15; //awas pin lima belas butuh low saat booting 
//const int relayPin = 2;
boolean mreset;
//const int rel2 = 15;  // masih penasaran ini rel2 untuk 

int number;             //digunakan untuk menampilkan number diseven segment
// Stores LED state
String ledState;        // digunakan untuk pertanda bahwa kondisi alarm aktive

int thn, bln, tgl, j, mnt, hr, dtk;                    //aDetik adalah variable  bepara kali berdetik buser alarm
int aJam, aMenit, aDetik, aHari, aaktif, aPilHar, aCerah; 
int aJam1, aMenit1, aDetik1, aaktif1, aPilHar1;
int aJam2, aMenit2, aDetik2, aaktif2, aPilHar2;
int aJam3, aMenit3, aDetik3, aaktif3, aPilHar3; 
int aJam4, aMenit4, aDetik4, aaktif4, aPilHar4;   

int aJamh, aMenith, aDetikh, aaktifh, aPilHarh; 
int aJam1h, aMenit1h, aDetik1h, aaktif1h, aPilHar1h;

unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
//unsigned long ml = 0;

//variabel parameter  7 segment
int sevJam, sevMinit;
int first_digit;
int second_digit;
int third_digit;
int forth_digit;
int i, i1, i2, i3, i4, i5, i6,i7, i8, i9, i10, i11, i12, i13;
int awal, awal1, awal2, awal3, awal4, awal5, awal6, awal7, awal8, awal9, awal10, awal11, awal12, awal13;
int onHour = 17;         // Jam untuk menyalakan relay (08:00)
int onMinute = 0;        // Menit untuk menyalakan relay
int onHari,offHari;
int offHour = 5;        // Jam untuk mematikan relay (17:00)
int offMinute = 0;       // Menit untuk mematikan relay

//alamat penyimpanan data alarm di eeprom
//int addrjam=10, addrmenit=20, addrlamanyalah = 30, addrhari nyalah = 40, addrnyalahon = 50 ;

boolean nyalahonhar, alarmstate;
boolean alarmon, aaktifon, alarmon1, aaktifon1, alarmon2, aaktifon2, alarmon3, aaktifon3, alarmon4,  aaktifon4;
boolean bataskedip, bataskedip1, bataskedip2, bataskedip3, bataskedip4;

int batasdetik, batasdetik1, batasdetik2, batasdetik3, batasdetik4;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;
Ticker wifiReconnectTimer;


void setup() {
  EEPROM.begin(512);
  unsigned int bacadelay = EEPROM.read(49);
  bacadelay=bacadelay*1000;
  //delay(bacadelay); //delay 20000 ini digunakan untuk memastikan jaringan terhubung dengan internet ketika PLN mati, kemudian PLN nyalah lagi
  // Serial port for debugging purposes
  Wire.begin();
  rtc.begin();

  Serial.begin(115200);
  
  
  int tesnilai50 = EEPROM.read(50);
  if (tesnilai50 == 0){
    alarmstate =false;  
  }else{
    alarmstate =true;
  }
  
  //========================scan dulu wifinya
  tes = scanDulu().c_str();
  Serial.println(tes);
  
//  pinMode(ledPin, OUTPUT); 
//  if (alarmstate==false){
//   digitalWrite(ledPin, HIGH);      //ingat ledpin gpionya sudah dipakai relay
//  } else {
//   digitalWrite(ledPin, LOW);
//  }

  // Mengatur intensitas (0-15)
  int tescerah80 = EEPROM.read(80);
  pinMode(kedip, OUTPUT);
  
  pinMode(RESET_BUTTON_PIN, INPUT);  // Use internal pull-up
  
  pinMode(BUZZ, OUTPUT);
  digitalWrite(BUZZ, HIGH);
  
  pinMode(rel, OUTPUT);
  digitalWrite(rel, HIGH);            //pakai gpio 02 yangjuga lednya board esp8266 dan pakai transistor pnp untuk mendukung boot

  //pinMode(rel2, OUTPUT);    //ini karena digunakan untuk tombol master reset eeprom 
  //digitalWrite(rel2, LOW);    //ini karena digunakan untuk tombol master reset eeprom 

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

//===================================== chek ssi dan password di eeprom
   int ssidLength = EEPROM.read(99);                        //awas ketika ic esp8266nya baru nilai eprom terbaca semuanya 255 .....
    ssid = "";
    for (int i = 0; i < ssidLength; ++i) {        
        ssid += char(EEPROM.read(100+i)); //1 + i));        //cara baca eeprom ini sama hasinya dengan di fungsi bacaEprom() buatan saya sendiri
    }                                                       // disini ditentukan pasti panjang eprom yang dibaca sedang di fungsi bacaeprom() saya
    Serial.println(ssid);                                   // panjang eprom yang dibaca sepanjang 32 charakter yang secara otomatis tidak membaca non karakter
    int passwordLength = EEPROM.read(149); //1 + ssidLength);
    password = "";                                                                                                                   
    for (int i = 0; i < passwordLength; ++i) {
        password += char(EEPROM.read(150+i)); //2 + ssidLength + i));
    }
    Serial.println(password);
    delay(3000);


  //  // Connect to Wi-Fi //ini jika esp bertindak ttidak sebagai accesspoint tapi konek ke sebuah jaringan wifi
  if (ssid.length() > 0 && password.length() > 0) {
      WiFi.begin(ssid.c_str(), password.c_str());
      Serial.print("Connecting to ");
      Serial.println(ssid);                                                                                                            
      int timeout = 20; // Try for ~10 seconds
      int y=0;
      while (WiFi.status() != WL_CONNECTED && y<20) {
        delay(500);
        Serial.print(".");
        //Serial.println("Connecting to WiFi..");
        y=y+1;
      }
      
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println(" Connected!");
        Serial.println(WiFi.localIP());
        Serial.println(WiFi.localIP()[0]);
        Serial.println(WiFi.localIP()[1]);
        Serial.println(WiFi.localIP()[2]);
        Serial.println(WiFi.localIP()[3]);
        Serial.println(WiFi.localIP()[4]);
        delay(3000);
      } else {
        Serial.println(" Failed. Starting AP mode...");
        //WiFi.disconnect();
        WiFi.mode(WIFI_AP);     //ini memastikan mode stasiun mati
        WiFi.softAP(ap_ssid, ap_password);
        //mencetak acces point
        IPAddress IP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(IP);
        Serial.println(IP[0]);
      }
      
  }else{
      WiFi.mode(WIFI_AP);   ////ini memastikan mode stasiun mati
      Serial.print("Setting AP (Access Point)..... apa ini gak jalan?");
      WiFi.softAP(ap_ssid, ap_password);
      Serial.println("Started Access Point");
      //mencetak acces point
      IPAddress IP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(IP);
  }
  //==============================coba yang ini: ======================
  Serial.printf("Connection status: %d\n", WiFi.status());

  
/*ini ditunda dulu masih bentrok dengan webserver
 * 
 * 
  //====================ini handle mqqt dan server
  jalankanMqtt();
  mqttClient.setServer(mqtt_broker, mqtt_port);
  connectToMqtt(); //ini baru mau jalan... tapi tetep ketika wifi terputus dia putus juga
  
*/


  //=========== ini routing web server dipindah di tab sendiri biar gak bingung terlalu panjang ================
  webserve();
  //====================================================
  server.serveStatic("/", SPIFFS, "/");
  
  // Start server
  server.begin();
  //server.handleClient();
  number = 1234; //Number to be   displayed
  disp.print(number); // Print the number

  if (WiFi.status() == WL_CONNECTED) {
   handleEmail(); //coba di refactory lagi agar ngirim emailnya tidak pas device dinyalakan 
                //ngirim emailnya 2-3 menit dari device nyalah, maksudnya setelah device terkonek dengan jaringan wifi 
                //hal ini dilakukan untuk memastikan email terkirim, bayangkan jika tai lampu maka email akan dikirim saat 
                //device hidup bukan saat device terhubung dengan jaringan yang terkoneksi internet....  
  }
}


void loop() {

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 2000) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    DateTime now = rtc.now(); //get the current date-time
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.date(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    sevJam = now.hour();
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    sevMinit = now.minute();
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    Serial.print(weekDay[now.dayOfWeek()]);
    Serial.println(now.dayOfWeek());
    Serial.println();
    
//    Serial.println(bacaEEPROM(100,132));
//    Serial.println(bacaEEPROM(150,182));
//    Serial.println(EEPROM.read(99));    
//    Serial.println(EEPROM.read(149));    
//    Serial.println(ssid);
//    Serial.println(password);
    
    number = (sevJam * 100) + sevMinit ;
    //Serial.println(number);

    //==========================alarm harian========================
    onHour = EEPROM.read(310);         // Jam untuk menyalakan relay (08:00)
    onMinute = EEPROM.read(320);       // Menit untuk menyalakan relay
    onHari = EEPROM.read(370);
    Serial.print("nyalah: ");
    Serial.print(onHour);
    Serial.print(":");
    Serial.println(onMinute);
    offHour = EEPROM.read(311);         // Jam untuk mematikan relay (17:00)
    offMinute = EEPROM.read(321);       // Menit untuk mematikan relay
    offHari = EEPROM.read(371);
    Serial.print("padam: ");
    Serial.print(offHour);
    Serial.print(":");
    Serial.println(offMinute);

    //===============================pengechekan alarm harian......
     if (shouldRelayBeOn()) {   //shouldRelayBeOn() ini membandingakan onday dan offDay lalu jamnya dan menitnya untuk menentukan 
        //digitalWrite(rel, LOW);   // mati atau hidupnya relay, buat fungsi baru yang akan mengecek 
        Serial.println("Relay harian ON");  // curentday apakah on tehadap nilai setingan jam on lalu mengechek curent day apakah 
      } else {                              // apakah off terhadap setingan jam of
        //digitalWrite(rel, HIGH);
        Serial.println("Relay harian OFF");
      }
      
    //===================================================================

    alarmstate = EEPROM.read(50);
//    Serial.print("kondisi state alarm: ");
//    Serial.println(alarmstate);
    
    aJam = EEPROM.read(10); 
    aMenit = EEPROM.read(20);
    aDetik = EEPROM.read(30);
    aaktif = EEPROM.read(60);
    aPilHar = EEPROM.read(70);
    //ini sebetulnya milik kecerahan==========
    aCerah = EEPROM.read(80);
    
    aJam1 = EEPROM.read(11); 
    aMenit1 = EEPROM.read(21);
    aDetik1 = EEPROM.read(31);
    aaktif1 = EEPROM.read(61);
    aPilHar1 = EEPROM.read(71);

    aJam2 = EEPROM.read(12); 
    aMenit2 = EEPROM.read(22);
    aDetik2 = EEPROM.read(32);
    aaktif2 = EEPROM.read(62);
    aPilHar2 = EEPROM.read(72);

    aJam3 = EEPROM.read(13); 
    aMenit3 = EEPROM.read(23);
    aDetik3 = EEPROM.read(33);
    aaktif3 = EEPROM.read(63);
    aPilHar3 = EEPROM.read(73);

    aJam4 = EEPROM.read(14); 
    aMenit4 = EEPROM.read(24);
    aDetik4 = EEPROM.read(34);
    aaktif4 = EEPROM.read(64);
    aPilHar4 = EEPROM.read(74);
    
    //awas ada kelemahan di function desimaltobinary yang hanya dibatasi 7 digit biner
    //akan jadi masalah jika alamat eeprom berisi data lebih besar dari 127
    if ((aPilHar>127)||(aPilHar1>127)||(aPilHar2>127)||(aPilHar3>127)||(aPilHar4>127)){  //ini untuk mengakali jika nilai eeeprom dialamat tersebut belum pernah disetting
      EEPROM.write(70,0);
      EEPROM.write(71,0);
      EEPROM.write(72,0);
      EEPROM.write(73,0);
      EEPROM.write(74,0);
      
      EEPROM.commit();
    }

    decToBinary(aPilHar,1);
    decToBinary(aPilHar1,2);
    decToBinary(aPilHar2,3);
    decToBinary(aPilHar3,4);
    decToBinary(aPilHar4,5);
    //Serial.println(pilhar[7]);

    //membuat biner alarm harian

    aPilHarh = EEPROM.read(370);
    aPilHar1h = EEPROM.read(371);
    decToBinaryh(aPilHarh,1);
    decToBinaryh(aPilHar1h,2);
    
/////////////////////////////////////////////////

    if ((pilhar[now.dayOfWeek()]==1)||(pilhar1[now.dayOfWeek()]==1)||(pilhar2[now.dayOfWeek()]==1)||(pilhar3[now.dayOfWeek()]==1)||(pilhar4[now.dayOfWeek()]==1)){        //(ahr[now.dayOfWeek()]==true){
      //Serial.println("hari ini ada alarm aktive");
      nyalahonhar=true;
    }else{
      //Serial.println("hari ini tidak ada alarm aktive");
      nyalahonhar=false;
    }
    //Serial.println(aaktif);
    //Serial.println(pilhar[1]);
    
    if ((aaktif==1)&&(pilhar[now.dayOfWeek()]==1)){
      aaktifon=true;
    }else{
      aaktifon=false;
    }
    if ((aaktif1==1)&&(pilhar1[now.dayOfWeek()]==1)) {    
      aaktifon1=true;
    }else{
      aaktifon1=false;
    }
    if ((aaktif2==1)&&(pilhar2[now.dayOfWeek()]==1)) {   
      aaktifon2=true;
    }else{
      aaktifon2=false;
    }
    if ((aaktif3==1)&&(pilhar3[now.dayOfWeek()]==1)) {   
      aaktifon3=true;
    }else{
      aaktifon3=false;
    }
    if ((aaktif4==1)&&(pilhar4[now.dayOfWeek()]==1)) {   
      aaktifon4=true;
    }else{
      aaktifon4=false;
    }

//    Serial.print("buzzer 1: ");
//    Serial.println(alarmon);
//    Serial.print("buzzer 2: ");
//    Serial.println(alarmon1);
//    Serial.print("buzzer 3: ");
//    Serial.println(alarmon2);
//    Serial.print("buzzer 4: ");
//    Serial.println(alarmon3);
//    Serial.print("buzzer 5: ");
//    Serial.println(alarmon4);

    //chek alarm ke1 ////////////////////////////////////////////////////////// 
     if (((aJam == sevJam) && (aMenit == sevMinit)) && (nyalahonhar==true) && (aaktifon==true)){ 
          if (bataskedip == false){
            Serial.print("ini jalannnnn ketika alarm1 on.......... ");
            alarmon=true;
            bataskedip=true;
          }
          //alarmon=false;
      }  
     
     //chek alarm ke2 ////////////////////////////////////////////////////////// 
     if (((aJam1 == sevJam) && (aMenit1 == sevMinit)) && (nyalahonhar==true) && (aaktifon1==true)){ 
          if (bataskedip1 == false){
            Serial.print("ini jalannnnn ketika alarm2 on.......... ");
            alarmon1=true;
            bataskedip1=true;
          }
          //alarmon=false;
      }
     
     //chek alarm ke3 ////////////////////////////////////////////////////////// 
     if (((aJam2 == sevJam) && (aMenit2 == sevMinit)) && (nyalahonhar==true) && (aaktifon2==true)){ 
          if (bataskedip2 == false){
            Serial.print("ini jalannnnn ketika alarm3 on.......... ");
            alarmon2=true;
            bataskedip2=true;
          }
          //alarmon=false;
      }    

      //chek alarm ke4 ////////////////////////////////////////////////////////// 
      if (((aJam3 == sevJam) && (aMenit3 == sevMinit)) && (nyalahonhar==true) && (aaktifon3==true)){ 
          if (bataskedip3 == false){
            Serial.print("ini jalannnnn ketika alarm4 on.......... ");
            alarmon3=true;
            bataskedip3=true;
          }
          //alarmon=false;
      }    

      //chek alarm ke5 ////////////////////////////////////////////////////////// 
      if (((aJam4 == sevJam) && (aMenit4 == sevMinit)) && (nyalahonhar==true) && (aaktifon4==true)){ 
          if (bataskedip4 == false){
            Serial.print("ini jalannnnn ketika alarm5 on.......... ");
            alarmon4=true;
            bataskedip4=true;
          }
          //alarmon=false;
      }    
  }

  
  //===================================timer ke dua untuk mengechek tombol reset eprom (devce) =========================
  
  if (digitalRead(RESET_BUTTON_PIN) == HIGH) {
    mreset=true;
  }else{
    mreset=false; 
  }
  
  unsigned long currentMillis2 = millis();
  if (currentMillis2 - previousMillis2 >= 4000) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis2;
    if (mreset == true) {
      delay(500);
      Serial.println("Reset button pressed. Clearing EEPROM...");
      clearEEPROM();
      delay(2000);  // Wait a bit
      ESP.restart();
    }


  //nitip mqtt====================================================
//  if (WiFi.status() == WL_CONNECTED) {
////    jalankanMqtt();
////    connectToMqtt();
//    
//  }



  
  // Publish sensor data via MQTT
    String payload = "  tes xxx"; //{\"temp\": 80 Celcius " + //String(temperature) + 
                    //",\"hum\": 90% " + "}";  //String(humidity) + "}";
    mqttClient.publish(mqtt_topic_pub, 1, true, payload.c_str());
//    Serial.println("========================>");
    //Serial.println(payload);
    
  }
  //=================================================================================
  
  if (alarmon==true){
      menghitungdetik();
  }
  if (alarmon1==true){
      menghitungdetik1();
  }
  if (alarmon2==true){
      menghitungdetik2();
  }
  if (alarmon3==true){
      menghitungdetik3();
  }
  if (alarmon4==true){
      menghitungdetik4();
  }
  
  //if (alarmstate==true){  
    //digitalWrite(ledPin, LOW);
  //}else{
    //digitalWrite(ledPin, HIGH);
  //}
  
  if ((alarmon==false)||(alarmon1==false)||(alarmon2==false)||(alarmon3==false)||(alarmon4==false)){
    digitalWrite(BUZZ,HIGH);    // ingat type PNP HIGH agar buzzer gak bunyi // tapi ini sudah aneh sebelumnya
  }
/* //ini dimatikan agar relay tidak terpengaruh alarm detikan
  if ((alarmon==true)||(alarmon1==true)||(alarmon2==true)||(alarmon3==true)||(alarmon4==true)){
    digitalWrite(rel, LOW);
    //digitalWrite(rel2, HIGH);  //ini karena digunakan untuk tombol master reset eeprom 
  }else{
    digitalWrite(rel, HIGH);
    //digitalWrite(rel2, LOW);  //ini karena digunakan untuk tombol master reset eeprom 
  }
*/
  disp.print(number); // Print the number
  //menambah nol
  if (sevJam < 10) {
    disp.set("zeros", 'y');
    //disp.print(number);
  }

  //ini untuk kedip titik dua////////////////////
  if (millis() % 1000 < 100) {
    digitalWrite(kedip, HIGH);
    //digitalWrite(rel, LOW);
    if ((alarmon==true)||(alarmon1==true)||(alarmon2==true)||(alarmon3==true)||(alarmon4==true)){
      digitalWrite(BUZZ, HIGH);
    }
  } else if (millis() % 1000 >= 100) {
    digitalWrite(kedip, LOW);
    //digitalWrite(rel, HIGH);
    if ((alarmon==true)||(alarmon1==true)||(alarmon2==true)||(alarmon3==true)||(alarmon4==true)){
      digitalWrite(BUZZ, LOW);
    }
  }

//  //ini meng-akali panjang detik alarm kurang dari satu menit
  if (aMenit != sevMinit){
     bataskedip = false;
  }
  if (aMenit1 != sevMinit){
     bataskedip1 = false;
  }
  if (aMenit2 != sevMinit){
     bataskedip2 = false;
  }
  if (aMenit3 != sevMinit){
     bataskedip3 = false;
  }
  if (aMenit4 != sevMinit){
     bataskedip4 = false;
  }


//=======================ini alarm harian=================
// Cek apakah waktu saat ini berada dalam jangka waktu aktif
  if (isTimeActive()) {
    digitalWrite(rel,LOW);      //relayPin, HIGH);
    //Serial.println("Relay ON");
  } else {
    digitalWrite(rel, HIGH);    //relayPin, LOW);
    //Serial.println("Relay OFF");
  }

//ini dipindah ke sub perdetik==============
//  if (shouldRelayBeOn()) {
//    //digitalWrite(rel, LOW);
//    Serial.println("Relay harian ON");
//  } else {
//    //digitalWrite(rel, HIGH);
//    Serial.println("Relay harian OFF");
//  }
  

}
/////////////////////////////////////////// end of void loop ///////////////////////////////////////////

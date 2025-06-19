void webserve(){
      
  // Route for root / web page (ini root nya)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to set GPIO to HIGH pertanda alarm on
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest * request) {
    //digitalWrite(ledPin, LOW);      //gpionya sudah dipakai relay
    EEPROM.write(50, 1);
    EEPROM.commit();
    alarmstate = true;
    request->send(SPIFFS, "/setalarm.html", String(), false, processor);
  });

  // Route to set GPIO to LOW pertanda alarm off
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest * request) {
    //digitalWrite(ledPin, HIGH);
    EEPROM.write(50, 0);
    EEPROM.commit();
    alarmstate = false;
    request->send(SPIFFS, "/setalarm.html", String(), false, processor);
  });

 //route untuk menampilkan state dari alarm apakah on ataukah off
  server.on("/state", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", state().c_str());
  });

  //route untuk menampilkan jam
  server.on("/jam", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getjam().c_str());
  });

  //route untuk menampilkan tanggal
  server.on("/tanggal", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", gettgl().c_str());
  });

  //route untuk manmpilkan nilai hari       //ini bisa distukan dengan get tgl....
  server.on("/hari", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", AngkaAcak().c_str());
  });

  //route untuk manmpilkan nilai setingan alarm ke 1
  server.on("/alarm", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", alarm().c_str());
  });

  //route untuk manmpilkan nilai setingan alarm ke 2
  server.on("/alarma", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", alarma().c_str());
  });

  //route untuk manmpilkan nilai setingan alarm ke 3
  server.on("/alarmb", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", alarmb().c_str());
  });
  
  //route untuk manmpilkan nilai setingan alarm ke 4
  server.on("/alarmc", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", alarmc().c_str());
  });

   //route untuk manmpilkan nilai setingan alarm ke 5
  server.on("/alarmd", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", alarmd().c_str());
  });

  
  //route untuk menampilkan setingan hari hari dimana alarm diaktifkan
  server.on("/alarm2", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", alarm2().c_str());
  });

  
  server.on("/teks1", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", teks1().c_str());
  });

  server.on("/teks2", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", teks2().c_str());
  });

  server.on("/teks3", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", teks3().c_str());
  });
  
  server.on("/cerah", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", cerah().c_str());
  });
  

//==========================================================
  //route untuk manmpilkan nilai setingan alarm harian ke 1
  server.on("/alarmh", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", alarmh().c_str());
  });

  //route untuk manmpilkan nilai setingan alarm harian ke 2
  server.on("/alarmah", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", alarmah().c_str());
  });
  /*


  ////////////ini routing scan wifi=========================
  server.on("/hasil", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", hasil().c_str());
  });

*/
  server.on("/scan", HTTP_GET, [](AsyncWebServerRequest * request) {
    //request->send_P(200, "text/plain", handleScan().c_str());
    //request->send(SPIFFS, "/setscan.html", String(), false, processor);
    request->send(200, "teks/json", tes.c_str());
  });
  

  //route untuk manangani data form inputan dikirim
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest * request) {
    String inputMessage1, inputMessage2, inputMessage3, inputMessage4, inputMessage5, inputMessage6, inputDetik6; //jam
    String inputMessage7, inputMessage8, inputMessage9, inputMessage10;             //alarm ke 1
    String inputMessage11, inputMessage12, inputMessage13, inputMessage14;          //alarm ke 2
    String inputMessage15, inputMessage16, inputMessage17, inputMessage18;          //alarm ke 3
    String inputMessage19, inputMessage20, inputMessage21, inputMessage22;          //alarm ke 4
    String inputMessage23, inputMessage24, inputMessage25, inputMessage26;          //alarm ke 5
    String inputMessage100;  //teksinput dari front end ssid
    String inputMessage101;  //kecerahan (kecerahan)
    String inputMessage102;  //pass
    String inputMessage103;  //email
    String inputMessage105, inputMessage106,  inputMessage107,  inputMessage108;    //alarm harian on
    String inputMessage109, inputMessage110,  inputMessage111,  inputMessage112;    //alarm harian on
        
    byte buff[7];   //ini menyusun hari dalam seminggu menjadi biner, tapi sudah tidak digunakan dibiarkan tidak dihapus biar bisa dipelajari

    if (request->hasParam("nama")) {      //ini menerima setjam =====================
      inputMessage1 = request->getParam("nama")->value();
      inputMessage2 = request->getParam("bulan")->value();
      inputMessage3 = request->getParam("tanggal")->value();
      inputMessage4 = request->getParam("jam")->value();
      inputMessage5 = request->getParam("menit")->value();
      if (request->hasParam("detik")) {    
          inputDetik6 = request->getParam("detik")->value();        
      }else{
        inputDetik6 ="0";
      }
      inputMessage6 = request->getParam("hari")->value();
      Serial.println(inputMessage1);
      Serial.println(inputMessage2);
      Serial.println(inputMessage3);
      Serial.println(inputMessage4);
      Serial.println(inputMessage5);
      Serial.println(inputDetik6);
      Serial.println(inputMessage6);
      thn = inputMessage1.toInt();
      bln = inputMessage2.toInt();
      tgl = inputMessage3.toInt();
      j = inputMessage4.toInt();
      mnt = inputMessage5.toInt();
      hr = inputMessage6.toInt();
      dtk = inputDetik6.toInt();
      if (thn!=0){
        DateTime dt(thn, bln, tgl, j, mnt, dtk, hr);
        rtc.setDateTime(dt);
        thn = 0;
      }
      request->send(SPIFFS, "/setjam.html", String(), false, processor);
    }

    if (request->hasParam("alarmjam")) {    //ini menerima setalarm ================================
      inputMessage7 = request->getParam("alarmjam")-> value();
      inputMessage8 = request->getParam("alarmmenit")-> value();    
      inputMessage9 = request->getParam("alarmdetik")-> value();
      inputMessage10 = request->getParam("integerhar")-> value();      
      
      inputMessage11 = request->getParam("alarmjam1")-> value();
      inputMessage12 = request->getParam("alarmmenit1")-> value();
      inputMessage13 = request->getParam("alarmdetik1")-> value();
      inputMessage14 = request->getParam("integerhar1")-> value();

      inputMessage15 = request->getParam("alarmjam2")-> value();
      inputMessage16 = request->getParam("alarmmenit2")-> value();
      inputMessage17 = request->getParam("alarmdetik2")-> value();     
      inputMessage18 = request->getParam("integerhar2")-> value();
      
      inputMessage19 = request->getParam("alarmjam3")-> value();
      inputMessage20 = request->getParam("alarmmenit3")-> value();
      inputMessage21 = request->getParam("alarmdetik3")-> value();     
      inputMessage22 = request->getParam("integerhar3")-> value();

      inputMessage23 = request->getParam("alarmjam4")-> value();
      inputMessage24 = request->getParam("alarmmenit4")-> value();
      inputMessage25 = request->getParam("alarmdetik4")-> value();     
      inputMessage26 = request->getParam("integerhar4")-> value();
            
      aJam = inputMessage7.toInt();
      aMenit = inputMessage8.toInt();
      aDetik = inputMessage9.toInt();
      aPilHar = inputMessage10.toInt();
      
      aJam1 = inputMessage11.toInt();
      aMenit1 = inputMessage12.toInt();
      aDetik1 = inputMessage13.toInt();  
      aPilHar1 = inputMessage14.toInt();

      aJam2 = inputMessage15.toInt();
      aMenit2 = inputMessage16.toInt();
      aDetik2 = inputMessage17.toInt();  
      aPilHar2 = inputMessage18.toInt();

      aJam3 = inputMessage19.toInt();
      aMenit3 = inputMessage20.toInt();
      aDetik3 = inputMessage21.toInt();  
      aPilHar3 = inputMessage22.toInt();

      aJam4 = inputMessage23.toInt();
      aMenit4 = inputMessage24.toInt();
      aDetik4 = inputMessage25.toInt();  
      aPilHar4 = inputMessage26.toInt();
      
      if (aJam<200){
        if (request->hasParam("aktif1")){
            EEPROM.write(60, 1);
        }else{
            EEPROM.write(60, 0);
        }
        if (inputMessage7!=""){
            EEPROM.write(10, aJam);
            EEPROM.write(20, aMenit);
            EEPROM.write(30, aDetik);
            EEPROM.write(70, aPilHar);          //menulis pilihan hari dalam bentuk integer ke eeprom
        }

        if (request->hasParam("aktif2")){
            EEPROM.write(61, 1);
        }else{
            EEPROM.write(61, 0);
        }
        if (inputMessage11!=""){
            EEPROM.write(11, aJam1);
            EEPROM.write(21, aMenit1);
            EEPROM.write(31, aDetik1);
            EEPROM.write(71, aPilHar1);
        }

        if (request->hasParam("aktif3")){
            EEPROM.write(62, 1);
        }else{
            EEPROM.write(62, 0);
        }
        if (inputMessage15!=""){
            EEPROM.write(12, aJam2);
            EEPROM.write(22, aMenit2);
            EEPROM.write(32, aDetik2);
            EEPROM.write(72, aPilHar2);
        }

        if (request->hasParam("aktif4")){
            EEPROM.write(63, 1);
        }else{
            EEPROM.write(63, 0);
        }
        if (inputMessage19!=""){
            EEPROM.write(13, aJam3);
            EEPROM.write(23, aMenit3);
            EEPROM.write(33, aDetik3);
            EEPROM.write(73, aPilHar3);
        }

        if (request->hasParam("aktif5")){
            EEPROM.write(64, 1);
        }else{
            EEPROM.write(64, 0);
        }
        if (inputMessage23!=""){
            EEPROM.write(14, aJam4);
            EEPROM.write(24, aMenit4);
            EEPROM.write(34, aDetik4);
            EEPROM.write(74, aPilHar4);
        }
        EEPROM.commit();

        aJam = 300;
      }
      

      //================ DI BAWAH INI SUDAH TIDAK DIGUNAKAN LAGI, EEPROM 41 SUDAH DIGANTIKAN EEPROM 70, 71, 72, 73, 74, 75, 76, 77,  dst =================//  
      //hanya dibutuhkan ada atau tidak ada parameter harinya untuk memberi nilai true di eeprom 
      //41 = minggu, 42 = senin, 43 = Selasa, 44 = rabu, 45 = kamis, 46 = jumat, 47 = sabtu.
      
      if (request->hasParam("Minggu")){
         buff[0]=1;
      }else{
         buff[0]=0;
      }
      if (request->hasParam("Senin")){
         buff[1]=1;
      }else{
         buff[1]=0;
      }
      if (request->hasParam("Selasa")){
         buff[2]=1;
      }else{
         buff[2]=0;
      }
      if (request->hasParam("Rabu")){
         buff[3]=1;
      }else{
         buff[3]=0;
      }
      if (request->hasParam("Kamis")){
         buff[4]=1;
      }else{
         buff[4]=0;
      }
      if (request->hasParam("Jumat")){
         buff[5]=1;
      }else{
         buff[5]=0;
      }
      if (request->hasParam("Sabtu")){
         buff[6]=1;
      }else{
         buff[6]=0;
      }
      for (int i = 0; i <7; i++) {
        ahr[i]=buff[i];
        EEPROM.write(41+i,buff[i]);
      }      
      if (EEPROM.commit()) {
        Serial.println("EEPROM successfully committed");
      } else {
        Serial.println("ERROR! EEPROM commit failed");
      }

      request->send(SPIFFS, "/setalarm.html", String(), false, processor);
    }

    
  //    request->send(SPIFFS, "/index.html", String(), false, processor);
    if  (request->hasParam("teksinput")){     //ini menerima setwifi ================================
      inputMessage100 = request->getParam("teksinput")-> value(); 
      inputMessage101 = request->getParam("kecerahan")-> value(); 
      inputMessage102 = request->getParam("teksinput1")-> value(); 
      inputMessage103 = request->getParam("teksinput2")-> value(); 
      String password = inputMessage100; //Serial.readString();
      String password1 = inputMessage102; //Serial.readString();
      String email = inputMessage103;
      aCerah = inputMessage101.toInt();
      EEPROM.write(49, aCerah);//80, aCerah);     //=================ingat kecerahan ditulis di alamat eprom 80
      
      //Serial.println(password);
      EEPROM.write(99, password.length());  //menulis panjang teks ssid dialamat eprom 99
      tulisEEPROM(password, 100);  //=================ingat password (nama ssid) ditulis di alamat eprom 100
      EEPROM.write(149, password1.length());  //menulis panjang karakter teks password dialamat eprom 149
      tulisEEPROM(password1, 150);   //=================ingat password1 (password wifi) ditulis di alamat eprom 150
      EEPROM.write(199, email.length());  //menulis panjang karakter email dialamat eprom 199
      tulisEEPROM(email, 200);   //=================ingat email notif ditulis di alamat eprom 200
      Serial.println(bacaEEPROM(100,132));  //===============membaca epprom dari alamat 100 samapai 132
      Serial.println(bacaEEPROM(150,182));  //================memebaca eprom dari alamat 150 - 182
      Serial.println(bacaEEPROM(200,232));  //================memebaca eprom dari alamat 150 - 182
      EEPROM.commit();
      
      request->send(SPIFFS, "/setwifi.html", String(), false, processor);
    }


     if (request->hasParam("alarmjamh")) {    //ini menerima setalarm HARIAN================================
      inputMessage105 = request->getParam("alarmjamh")-> value();
      inputMessage106 = request->getParam("alarmmenith")-> value();    
      inputMessage107 = request->getParam("alarmdetikh")-> value();
      inputMessage108 = request->getParam("integerharh")-> value();      
      
      inputMessage109 = request->getParam("alarmjam1h")-> value();
      inputMessage110 = request->getParam("alarmmenit1h")-> value();
      inputMessage111 = request->getParam("alarmdetik1h")-> value();
      inputMessage112 = request->getParam("integerhar1h")-> value();

      aJamh = inputMessage105.toInt();
      aMenith = inputMessage106.toInt();
      aDetikh = inputMessage107.toInt();
      aPilHarh = inputMessage108.toInt();
      
      aJam1h = inputMessage109.toInt();
      aMenit1h = inputMessage110.toInt();
      aDetik1h = inputMessage111.toInt();  
      aPilHar1h = inputMessage112.toInt();

       if (aJamh<200){ //ini hanya memastikan
        if (request->hasParam("aktif1h")){
            EEPROM.write(360, 1);
        }else{
            EEPROM.write(360, 0);
        }
        if (inputMessage105!=""){
            EEPROM.write(310, aJamh);
            EEPROM.write(320, aMenith);
            EEPROM.write(330, aDetikh);
            EEPROM.write(370, aPilHarh);          //menulis pilihan hari dalam bentuk integer ke eeprom
        }

        if (request->hasParam("aktif2h")){
            EEPROM.write(361, 1);
        }else{
            EEPROM.write(361, 0);
        }
        if (inputMessage109!=""){
            EEPROM.write(311, aJam1h);
            EEPROM.write(321, aMenit1h);
            EEPROM.write(331, aDetik1h);
            EEPROM.write(371, aPilHar1h);
        }
       }
       EEPROM.commit();
        
       aJamh = 300;
      
      request->send(SPIFFS, "/setalarmhar.html", String(), false, processor);
     }
    
  });

}

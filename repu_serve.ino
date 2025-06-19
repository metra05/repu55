String state() {
  //DateTime now = rtc.now();
  int tesnilai50 = EEPROM.read(50);
   char buff[10];
  if (tesnilai50 == 0){
     alarmstate =false;  
     sprintf(buff, "OFF");
  }else{
    alarmstate =true;
    sprintf(buff, "ON");
  }
  return String(buff);
}

String getjam() {
  DateTime now = rtc.now();
  int ja = now.hour();
  int me = now.minute();
  int det = now.second();
  char buffer[20];
  sprintf(buffer, "%d : %d : %d", ja, me, det);
  return String(buffer);
}

String gettgl() {
  DateTime now = rtc.now();
  int th = now.year(); 
  int bl = now.month(); 
  int tg = now.date();
  char buffer[20];
  sprintf(buffer, "%d / %d / %d", tg, bl, th);
//  sprintf(buffer, "%s, %d / %d / %d", weekDay[now.dayOfWeek()], tg, bl, th);
  return String(buffer);
}

String AngkaAcak() {
  DateTime now = rtc.now();
  return String(weekDay[now.dayOfWeek()]); //ini return string, nama hari
}

String alarm(){
   int valueaJam = EEPROM.read(10);
   int valueaMenit = EEPROM.read(20);
   int valueLamadetik = EEPROM.read(30);
   int valueAktif= EEPROM.read(60);
   int valueHari = EEPROM.read(70);    
   char buffer[40];
   sprintf(buffer, "%d %d %d %d %d", valueaJam, valueaMenit, valueLamadetik, valueAktif, valueHari );
   return String(buffer);
}

String alarma(){
   int valueaJam = EEPROM.read(11);
   int valueaMenit = EEPROM.read(21);
   int valueLamadetik = EEPROM.read(31);
   int valueAktif= EEPROM.read(61);
   int valueHari = EEPROM.read(71);    
   char buffer[40];
   sprintf(buffer, "%d %d %d %d %d", valueaJam, valueaMenit, valueLamadetik, valueAktif, valueHari );
   return String(buffer);
}

String alarmb(){
   int valueaJam = EEPROM.read(12);
   int valueaMenit = EEPROM.read(22);
   int valueLamadetik = EEPROM.read(32);
   int valueAktif= EEPROM.read(62);
   int valueHari = EEPROM.read(72);    
   char buffer[40];
   sprintf(buffer, "%d %d %d %d %d", valueaJam, valueaMenit, valueLamadetik, valueAktif, valueHari );
   return String(buffer);
}

String alarmc(){
   int valueaJam = EEPROM.read(13);
   int valueaMenit = EEPROM.read(23);
   int valueLamadetik = EEPROM.read(33);
   int valueAktif= EEPROM.read(63);
   int valueHari = EEPROM.read(73);    
   char buffer[40];
   sprintf(buffer, "%d %d %d %d %d", valueaJam, valueaMenit, valueLamadetik, valueAktif, valueHari );
   return String(buffer);
}

String alarmd(){
   int valueaJam = EEPROM.read(14);
   int valueaMenit = EEPROM.read(24);
   int valueLamadetik = EEPROM.read(34);
   int valueAktif= EEPROM.read(64);
   int valueHari = EEPROM.read(74);    
   char buffer[40];
   sprintf(buffer, "%d %d %d %d %d", valueaJam, valueaMenit, valueLamadetik, valueAktif, valueHari );
   return String(buffer);
}

String alarm2(){
   char har[7];
   char bon;
   int valueBooting = EEPROM.read(49);    //ini dari mana asalnya?
   for (int i = 0; i <7; i++) {
       har[i]= EEPROM.read(41+i);
   }
   int multiplier = 1;                //menyusun bilangan biner
   for (int i = 6; i >= 0; --i ){
       bon += (multiplier * har[i]);
       //multiplier *= 10;
       multiplier *=2;
   }   
   char buff[10];
   //sprintf(buff,"%d",bon);
   sprintf(buff,"%d",valueBooting);
   return String(buff);
}

///////////////////////////////////////////////
String teks1(){
  //Serial.println(bacaEEPROM(100,132));
   return String(bacaEEPROM(100,132));
}

String teks2(){
   return String(bacaEEPROM(150,182));
}


String teks3(){
   return String(bacaEEPROM(200,232));
}


String cerah(){
  char buff[10];
  int valuecerah= EEPROM.read(49);  //80); //8o ini untuk kecerahan pada led matrix 
  sprintf(buff,"%d",valuecerah);
   return String(buff);
}
/////////////////////////////////////////////////////////
//alarm harian
String alarmh(){
   int valueaJam = EEPROM.read(310);
   int valueaMenit = EEPROM.read(320);
   int valueLamadetik = EEPROM.read(330);
   int valueAktif= EEPROM.read(360);
   int valueHari = EEPROM.read(370);    
   //Serial.println(valueHari);
   char buffer[40];
   sprintf(buffer, "%d %d %d %d %d", valueaJam, valueaMenit, valueLamadetik, valueAktif, valueHari );
   return String(buffer);
}

String alarmah(){
   int valueaJam = EEPROM.read(311);
   int valueaMenit = EEPROM.read(321);
   int valueLamadetik = EEPROM.read(331);
   int valueAktif= EEPROM.read(361);
   int valueHari = EEPROM.read(371);    
   char buffer[40];
   sprintf(buffer, "%d %d %d %d %d", valueaJam, valueaMenit, valueLamadetik, valueAktif, valueHari );
   return String(buffer);
}

///////////////////////////////////

// Replaces placeholder with LED state value
String processor(const String& var) {
  //Serial.println(var);
  if (var == "STATE") {
    int nilaistate = EEPROM.read(50);
    if (nilaistate==0) {
      ledState = "OFF";
    }
    else {
      ledState = "ON";
    }
    //Serial.print(ledState);
    return ledState;
  }
  else if (var == "JAM") {
    return getjam();
  }
  else if (var == "TANGGAL") {
    return gettgl();
  }
  else if (var == "HARI") {
    return AngkaAcak();  
  }
    else if (var == "ALARM") {
    return alarm();                //ini menampilkan jam:menit alarm1  
  }
    else if (var == "ALARMA") {
    return alarma();               //ini menampilkan jam:menit alarm2  
  }
    else if (var == "ALARMB") {
    return alarmb();               //ini menampilkan jam:menit alarm3  
  }
    else if (var == "ALARMC") {
    return alarmc();               //ini menampilkan jam:menit alarm4  
  }
    else if (var == "ALARMD") {
    return alarmd();               //ini menampilkan jam:menit alarm5  
  }
    else if (var == "ALARM2") {
    return alarm2();            //ini menampilkan hari ini ada alarm
  }
   else if (var == "TEKS1") {
    return teks1();   //ini menampilkan nama ssid setingan wifi
  }
   else if (var == "TEKS2") {
    return teks2();   //ini menampilkan password setingan wifi
  }
   else if (var == "TEKS3") {
    return teks2();   //ini menampilkan alamat email notif
  }
  else if (var == "CERAH") {
    return cerah();   //ini menampilkan set kecerahan
  }
  else if (var == "HASIL") {
    return hasil();   //ini menampilkan set kecerahan
  }
  else if (var == "ALARMH") {
    return alarmh();                //ini menampilkan jam:menit alarm harian1  
  }
  else if (var == "ALARMAH") {
    return alarmah();               //ini menampilkan jam:menit alarm harian2  
  }
  return "ada yang error";
}

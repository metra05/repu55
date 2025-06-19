//alarm tanpa chek hari=========================================================

bool isTimeActive(){  //DateTime now) {
  DateTime now = rtc.now();
  // Konversi waktu saat ini, waktu nyala, dan waktu mati ke menit
  int currentMinutes = now.hour() * 60 + now.minute();
  int onMinutes = onHour * 60 + onMinute;     //8:00
  int offMinutes = offHour * 60 + offMinute;  //17:00
  
  // Jika waktu nyala lebih kecil dari waktu mati (dalam hari yang sama)
  if (onMinutes < offMinutes) {
    return (currentMinutes >= onMinutes && currentMinutes < offMinutes);
  } 
  // Jika waktu nyala lebih besar dari waktu mati (melewati tengah malam)
  else if (onMinutes > offMinutes) {
    return (currentMinutes >= onMinutes || currentMinutes < offMinutes);
  }
  
  return false; // Jika waktu nyala dan mati sama

}



//coba bikin chek hari ==================================================
/*
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

const int relayPin = 8; // Pin yang terhubung ke relay

// Waktu dan hari untuk menyalakan relay
int onDay = 1;       // Hari (1=Senin, 2=Selasa, ..., 7=Minggu)
int onHour = 8;       // Jam untuk menyalakan relay (08:00)
int onMinute = 0;     // Menit untuk menyalakan relay

// Waktu dan hari untuk mematikan relay
int offDay = 5;       // Hari (1=Senin, 2=Selasa, ..., 7=Minggu)
int offHour = 17;     // Jam untuk mematikan relay (17:00)
int offMinute = 0;    // Menit untuk mematikan relay

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Pastikan relay mati saat mulai
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Jika RTC kehilangan daya, atur waktu ke waktu kompilasi
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();
  
  // Dapatkan hari dalam minggu (1=Senin, 7=Minggu)
  int currentDay = now.dayOfTheWeek();
  if (currentDay == 0) currentDay = 7; // Beberapa library return 0 untuk Minggu
  
  Serial.print("Hari: ");
  Serial.print(getDayName(currentDay));
  Serial.print(", Waktu: ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  ///////=============================================================================
  // Cek apakah waktu saat ini berada dalam jangka waktu aktif
  if (shouldRelayBeOn(now, currentDay)) {
    digitalWrite(relayPin, HIGH);
    //Serial.println("Relay ON");
  } else {
    digitalWrite(relayPin, LOW);
    //Serial.println("Relay OFF");
  }
//=====================================================================================  

  delay(1000); // Periksa setiap detik
}
*/

bool shouldRelayBeOn() {// yang harusnya masuk sini parameter: aPilHarh[], aPilHar1h[], onHour, offHour, onMinute, offMinute
  int onDay;
  int offDay;
  int offday_sebe=0;
  int offday_sesu=0;
  
  DateTime now = rtc.now();
  int currentDay = now.dayOfWeek();
  // Konversi waktu saat ini, waktu nyala, dan waktu mati ke menit
  int currentMinutes = now.hour() * 60 + now.minute();
  int onMinutes = onHour * 60 + onMinute;
  int offMinutes = offHour * 60 + offMinute;
  boolean posision=false; //, posisioff; //false true ini menentukan berada dibawah curentday atau diatas current day
  boolean posisioff=false;
//  boolean posisioff_sebe, posisioff_sesu;

  //mulai sini dicari ketemu hari onDay dan onOff yang terdekat yang aktif sesuai isi apilhar[] curenntday menentukan posisi pengechekkan hari yang kosong
  //EEPROM.read(370);
   if (aPilHarh==0){     //onHari==0){  //ohHari tidak dipakai    //manual mati alarm tidak aktif
    return false;
   }else if(aPilHarh<=127 && aPilHar1h==0){    //manual nyalah alarm aktif tiap alarm tidak dimatikan
    return true; 
   }
   
   Serial.print(pilharh[0]);
   Serial.print(pilharh[1]);
   Serial.print(pilharh[2]);
   Serial.print(pilharh[3]);
   Serial.print(pilharh[4]);
   Serial.print(pilharh[5]);
   Serial.println(pilharh[6]);   

   //ini menetukan onDay
   if (pilharh[currentDay]==1 && onMinutes<=currentMinutes){  
        onDay=currentDay;
        Serial.print("nilai onday adalah: sama dengan currentday");
        Serial.println(onDay);
   }else if(currentDay>=0) {
     for(int i=0; i<=currentDay; i++){
      if(pilharh[currentDay-i]==1){
        onDay=currentDay-i;
        Serial.print("ditemukan nilai onDay sebelum currentday: "); //chek apakah ada ada offday yang juga sbelum curent day tapi nilainya mengoffkan
        Serial.println(onDay);
        posision=true;
        break; 
      }
     }
     if (posision==false){ //posision belum ditemukan seharusnya ada diatas curent day
       for(int i=0; i<=(6-currentDay); i++){
//        Serial.print("Nilai i: ");
//        Serial.println(i); //debuging
        if(pilharh[currentDay+i]==1){
           onDay=currentDay+i;
           Serial.print("ditemukan nilai onDay setelah currentday: "); //dichek juga jika ada nilai nilai onday yang lebih besar dari offday setelah current day
           Serial.println(onDay);
           posision=false;
           break; 
        }
     }
    }
   }// sampai sini seharusnya sudah ditemukan posisi onDay
//========================================================================

   Serial.print(pilhar1h[0]);
   Serial.print(pilhar1h[1]);
   Serial.print(pilhar1h[2]);
   Serial.print(pilhar1h[3]);
   Serial.print(pilhar1h[4]);
   Serial.print(pilhar1h[5]);
   Serial.println(pilhar1h[6]);  
   
   Serial.print("Nilai offday: ");
   Serial.println(offDay);
   Serial.print("Nilai currentday: ");
   Serial.println(currentDay);// sampai si
   //ini menetukan offDay
   if (pilhar1h[currentDay]==1 && (offMinutes<=currentMinutes)){  
     
        offDay=currentDay;
        Serial.println("nilai offDay adalah: sama dengan currentday");
        Serial.println(offDay);
     
   }else if(currentDay>=0) {
     for(int i=0; i<=(6-currentDay); i++){
//      Serial.print("Nilai i: ");
//      Serial.println(i); //debuging
      if(pilhar1h[currentDay+i]==1){     
        offDay=currentDay+i;
        Serial.print("ditemukan nilai offDay setelah currentday: ");
        Serial.println(offDay);
        posisioff=true;
        
        //sub ini untuk menentukan apakah ada offday sebelum currentday tapi setelah onday
        if (posision==true){
          //
            for(int i=0; i<=currentDay; i++){
             if(pilhar1h[currentDay-i]==1){
               //offDay=currentDay-i;
               offday_sebe=currentDay-i;
               Serial.print("ditemukan nilai offDay sebelum currentday dibandingkan dengan onday -->  ");
               Serial.println(offday_sebe);
               if (offday_sebe==onDay && offMinutes>=onMinutes){ //pastikan juga jam dan menitnya lebih besar dan 
                offDay=offday_sebe;
                posisioff=false;
               }else if (offday_sebe>onDay){
                offDay=offday_sebe;
                posisioff=false;
               }else{
                posisioff=true;
               }
               Serial.print("nilai posisioff: ");
               Serial.println(posisioff);
               Serial.print("nilai offday: ");
               Serial.println(offDay);
               break; 
             }
            }
          //
        }else if (posision==false){ 
          for(int i=0; i<=(6-currentDay); i++){   //ini mencari ofday jika onday ditemukan setelah currentday dan sebelum curentday ofdaynya 
             Serial.print("Nilai i: ");
             Serial.println(i); //debuging
             if(pilhar1h[6-i]==1){
               //offDay=currentDay-i;
               offday_sesu=6-i;
               offDay=offday_sesu;
               Serial.print("nilai offday: ");
               Serial.println(offDay);
               break;
             }
          }
        }
        
        break; 
      }
     }
     
     if (posisioff==false){ //posisi off belum ditemukan
       for(int i=0; i<=currentDay; i++){
       if(pilhar1h[currentDay-i]==1){
         offDay=currentDay-i;
         Serial.print("ditemukan nilai offDay sebelum currentday: ");
         Serial.println(offDay);
         posisioff=false;
         break; 
       }
      }
    }
   }
   
 //  Serial.print("Nilai offday nya: ");
 //  Serial.println(offDay);// sampai sini seharusnya sudah ditemukan posisi offDay

   if (onDay > 7){
    Serial.println("error pada nilai onDay periksa koneksi ds3231");
    return false;
   }
   
  // Jika hari saat ini antara hari nyala dan hari mati /////////onDay dan onHari ini array dari apilhar[]
  if (onDay < offDay) {
    if (currentDay > onDay && currentDay < offDay) {
      return true;
    }
  } 
  
  // Jika melewati akhir minggu (misal nyala Jumat, mati Senin)
  else if (onDay > offDay) {
    if (currentDay > onDay || currentDay < offDay) {
      return true;
    }
  }
  
  // Jika hari saat ini sama dengan hari nyala atau hari mati
  if (currentDay == onDay || currentDay == offDay) {
    // Pada hari nyala, periksa apakah sudah lewat waktu nyala
    if (currentDay == onDay && currentMinutes >= onMinutes) {
      return true;
    }
    // Pada hari mati, periksa apakah belum lewat waktu mati
    else if (currentDay == offDay && currentMinutes < offMinutes) {
      return true;
    }
    // Kasus khusus ketika nyala dan mati di hari yang sama
    else if (onDay == offDay) {
      if (onMinutes < offMinutes) {
        return (currentMinutes >= onMinutes && currentMinutes < offMinutes);
      } else {
        return (currentMinutes >= onMinutes || currentMinutes < offMinutes);
      }
    }
    
  }
  
  return false;
}

//
//String getDayName(int day) {
//  switch(day) {
//    case 1: return "Senin";
//    case 2: return "Selasa";
//    case 3: return "Rabu";
//    case 4: return "Kamis";
//    case 5: return "Jumat";
//    case 6: return "Sabtu";
//    case 7: return "Minggu";
//    default: return "Tidak diketahui";
//  }
//}
  

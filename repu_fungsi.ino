
//ini gak efektif coba di refactoring lagi fungsinya.........
void menghitungdetik()
  {
    aDetik = EEPROM.read(30);
    batasdetik = aDetik;
    DateTime now = rtc.now(); //get the current date-time
    if (awal != now.second()){
      i=i+1;
      awal=now.second();
      Serial.println(i);
    }
    if (i >= batasdetik){
        Serial.println(bataskedip); 
        alarmon = false;
        Serial.println("ini dijalankan");
        Serial.println(alarmon);   
        i=0;
        awal=0;                
     }
  }

void menghitungdetik1()
  {
    aDetik1 = EEPROM.read(31);
    batasdetik1 = aDetik1;
    DateTime now = rtc.now(); //get the current date-time
    if (awal1 != now.second()){
      i1=i1+1;
      awal1=now.second();
      Serial.println(i1);
    }
    if (i1 >= batasdetik1){
        Serial.println(bataskedip1); 
        alarmon1 = false;
        Serial.println("ini dijalankan");
        Serial.println(alarmon1);   
        i1=0;
        awal1=0;                
     }
  }

void menghitungdetik2()
  {
    aDetik2 = EEPROM.read(32);
    batasdetik2 = aDetik2;
    DateTime now = rtc.now(); //get the current date-time
    if (awal2 != now.second()){
      i2=i2+1;
      awal2=now.second();
      Serial.println(i2);
    }
    if (i2 >= batasdetik2){
        Serial.println(bataskedip2); 
        alarmon2 = false;
        Serial.println("ini dijalankan");
        Serial.println(alarmon2);   
        i2=0;
        awal2=0;                
     }  
  }
  
  void menghitungdetik3()
  {
    aDetik3 = EEPROM.read(33);
    batasdetik3 = aDetik3;
    DateTime now = rtc.now(); //get the current date-time
    if (awal3 != now.second()){
      i3=i3+1;
      awal3=now.second();
      Serial.println(i3);
    }
    if (i3 >= batasdetik3){
        Serial.println(bataskedip3); 
        alarmon3 = false;
        Serial.println("ini dijalankan");
        Serial.println(alarmon3);   
        i3=0;
        awal3=0;                
     }  
  }

  void menghitungdetik4()
  {
    aDetik4 = EEPROM.read(34);
    batasdetik4 = aDetik4;
    DateTime now = rtc.now(); //get the current date-time
    if (awal4 != now.second()){
      i4=i4+1;
      awal4=now.second();
      Serial.println(i4);
    }
    if (i4 >= batasdetik4){
        Serial.println(bataskedip4); 
        alarmon4 = false;
        Serial.println("ini dijalankan");
        Serial.println(alarmon4);   
        i4=0;
        awal4=0;                
     }  
  }


/////////////////////////////////////////////////////////////
//desimal menjadi biner
void decToBinary(int n, int d)
{
    // array to store binary number
    int binaryNum[7];
    //byte binarynum1[7];
    int u=0;
    // counter for binary array
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int k=0; k<7-i ;k++){
      binaryNum[k+i]=0;  
    }
    // printing binary array in reverse order //membalik urutan binernya sekaligus memasukkan ke variable set hari masing masing alarm
    for (int j = 7 - 1; j >= 0; j--){
        if (d==1){
          pilhar[u]=binaryNum[j];
          u=u+1;
        }else if(d==2){
          pilhar1[u]=binaryNum[j];
          u=u+1;
        }else if(d==3){
          pilhar2[u]=binaryNum[j];
          u=u+1;
        }else if(d==4){
          pilhar3[u]=binaryNum[j];
          u=u+1;
        }else if(d==5){
          pilhar4[u]=binaryNum[j];
          u=u+1;
        }
    }
}



/////////////////////////////////////////////////////////////
//desimal menjadi biner alarm harian
void decToBinaryh(int n, int d)
{
    // array to store binary number
    int binaryNum[7];
    //byte binarynum1[7];
    int u=0;
    // counter for binary array
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int k=0; k<7-i ;k++){
      binaryNum[k+i]=0;  
    }
    // printing binary array in reverse order //membalik urutan binernya sekaligus memasukkan ke variable set hari masing masing alarm
    for (int j = 7 - 1; j >= 0; j--){
        if (d==1){
          pilharh[u]=binaryNum[j];
          u=u+1;
        }else if(d==2){
          pilhar1h[u]=binaryNum[j];
          u=u+1;
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////

void tulisEEPROM(String buffer, int N) {      //untuk menulis kirim string dan alamat eprom mulai 
  //EEPROM.begin(512); //delay(10);           //(dalam hal ini panjangnya 32 karakter) ditulis mulai alamat 100
  //int colonPosition = buffer.indexOf(' ');
  //buffer.setCharAt(colonPosition, 'Q');
  for (int L = 0; L < 32; ++L) {
      EEPROM.write(N + L, buffer[L]);
  }
  EEPROM.commit();
}
//
String bacaEEPROM(int min, int max) {        //untuk membacaparameternya alam,at awal eeprom dan alamat akhir eeprom panjang alamat 100-132
  //EEPROM.begin(512); //delay(10); 
  String buffer;
  for (int L = min; L < max; ++L)
    //if (isAlphaNumeric(EEPROM.read(L)))
      buffer += char(EEPROM.read(L));
  return buffer;
}


//===========clear eprom dan reset

void clearEEPROM() {
  EEPROM.begin(512);
  for (int i = 0; i < 512; ++i) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  Serial.println("EEPROM cleared");
}




//////////////////////////////////////////////////////////////////////////////////////////

// digunakan untuk menghitung hari pasaran
int jumlahhari(){ 
      DateTime now = rtc.now(); 
      int d= now.date();
      int m= now.month();
      int y= now.year();
      int hb[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
      int ht = (y - 1970) * 365 - 1;
      int hs = hb[m - 1] + d;
      int kab = 0;
      int i;
      if(y % 4 == 0) {
        if(m > 2) {
        hs++;
        }
      }
      for(i = 1970; i < y; i++) {
        if(i % 4 == 0) {
        kab++;
        }
      }
      return (ht + hs + kab); 
 }
//pasar[jumlahhari()%5]
  

  
  

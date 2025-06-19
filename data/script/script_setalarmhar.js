
	//mencoba mengganti set interval dengan event tombol kirim diclik
  //setInterval(function ( ) { //====== blok ini tidak perlu dipanggil secara interval cukup sekali pas loading
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("state").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/state", true);
  xhttp.send();
//}, 1000 ) ; //ini tes...........................................

//menampilkan jam alarm
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      //document.getElementById("alarm").innerHTML = this.responseText;
      var alrmaray=this.responseText;
      var myarray= alrmaray.split(" ");
      document.getElementById("alarmh").innerHTML = myarray[0] + " : "+myarray[1] + " Selama: " + myarray[2]+ ", int:" + myarray[4];//this.responseText;
      document.getElementById("alarmjamh").value = myarray[0];
      document.getElementById("alarmmenith").value = myarray[1];
      document.getElementById("alarmdetikh").value = myarray[2];
      if (myarray[3]==1){ 
        document.getElementById("aktif1h").checked=true;
      }else {
        document.getElementById("aktif1h").checked=false;
      }
      var bin = loopInInterval(+myarray[4], "1");
      document.getElementById("alarm2").innerHTML = bin;  //ini menampilkan hari alarm aktiv hanya untuk alarm ini saja
      document.getElementById("sembunyih").value = myarray[4];
    }
  };
  xhttp.open("GET", "/alarmh", true);
  xhttp.send();

//menampilkan jam alarm ke 2
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var alrmaray=this.responseText;
      var myarray= alrmaray.split(" ");
      document.getElementById("alarmah").innerHTML = myarray[0] + " : "+myarray[1] + " Selama: " + myarray[2] + ", int:" + myarray[4];//this.responseText;
      document.getElementById("alarmjam1h").value = myarray[0];
      document.getElementById("alarmmenit1h").value = myarray[1];
      document.getElementById("alarmdetik1h").value = myarray[2];
      if (myarray[3]==1){ 
        document.getElementById("aktif2h").checked=true;
      }else {
        document.getElementById("aktif2h").checked=false;
      }
      var bin = loopInInterval(+myarray[4], "2");
      document.getElementById("sembunyi1h").value = myarray[4];
    }
  };
  xhttp.open("GET", "/alarmah", true);
  xhttp.send();


//   //menampilkan jam alarm ke 3
//   var xhttp = new XMLHttpRequest();
//   xhttp.onreadystatechange = function() {
//     if (this.readyState == 4 && this.status == 200) {
//       var alrmaray=this.responseText;
//       var myarray= alrmaray.split(" ");
//       document.getElementById("alarmb").innerHTML = myarray[0] + " : "+myarray[1] + " Selama: " + myarray[2] + ", int:" + myarray[4];//this.responseText;
//       document.getElementById("alarmjam2").value = myarray[0];
//       document.getElementById("alarmmenit2").value = myarray[1];
//       document.getElementById("alarmdetik2").value = myarray[2];
//       if (myarray[3]==1){ 
//         document.getElementById("aktif3").checked=true;
//       }else {
//         document.getElementById("aktif3").checked=false;
//       }
//       var bin = loopInInterval(+myarray[4], "3");
//       document.getElementById("sembunyi2").value = myarray[4];
//     }
//   };
//   xhttp.open("GET", "/alarmb", true);
//   xhttp.send();


//  //menampilkan jam alarm ke 4
//   var xhttp = new XMLHttpRequest();
//   xhttp.onreadystatechange = function() {
//     if (this.readyState == 4 && this.status == 200) {
//       var alrmaray=this.responseText;
//       var myarray= alrmaray.split(" ");
//       document.getElementById("alarmc").innerHTML = myarray[0] + " : "+myarray[1] + " Selama: " + myarray[2] + ", int:" + myarray[4];//this.responseText;
//       document.getElementById("alarmjam3").value = myarray[0];
//       document.getElementById("alarmmenit3").value = myarray[1];
//       document.getElementById("alarmdetik3").value = myarray[2];
//       if (myarray[3]==1){ 
//         document.getElementById("aktif4").checked=true;
//       }else {
//         document.getElementById("aktif4").checked=false;
//       }
//       var bin = loopInInterval(+myarray[4], "4");
//       document.getElementById("sembunyi3").value = myarray[4];
//     }
//   };
//   xhttp.open("GET", "/alarmc", true);
//   xhttp.send();

//  //menampilkan jam alarm ke 5
//   var xhttp = new XMLHttpRequest();
//   xhttp.onreadystatechange = function() {
//     if (this.readyState == 4 && this.status == 200) {
//       var alrmaray=this.responseText;
//       var myarray= alrmaray.split(" ");
//       document.getElementById("alarmd").innerHTML = myarray[0] + " : "+myarray[1] + " Selama: " + myarray[2] + ", int:" + myarray[4];//this.responseText;
//       document.getElementById("alarmjam4").value = myarray[0];
//       document.getElementById("alarmmenit4").value = myarray[1];
//       document.getElementById("alarmdetik4").value = myarray[2];
//       if (myarray[3]==1){ 
//         document.getElementById("aktif5").checked=true;
//       }else {
//         document.getElementById("aktif5").checked=false;
//       }
//       var bin = loopInInterval(+myarray[4], "5");
//       document.getElementById("sembunyi4").value = myarray[4];
//     }
//   };
//   xhttp.open("GET", "/alarmd", true);
//   xhttp.send();




//menampilkan setingan hari-hari (alarm2)
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var angka = this.responseText;
      var angkadec = +angka;  //merubah jadi int
      ////////////   SEPERINYA SUB ROUTIN FUNGSI %ALARM2% INI TIODAK DIBUTHKAN LAGI  //////////////////////////
    };
  };
  xhttp.open("GET", "/alarm2", true);
  xhttp.send();


  function kirimAH(){
    let binn=[];
    let binn1=[];
    // let binn2=[];
    // let binn3=[];
    // let binn4=[];

    let har=["Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"];
    let ph=document.getElementById("pilihhar1");
    let ph1=document.getElementById("pilihhar2");
    // let ph2=document.getElementById("pilihhar3");
    // let ph3=document.getElementById("pilihhar4");
    // let ph4=document.getElementById("pilihhar5");
   
    for (i=0;i<7;i++){    //menyusun nilai binernya
      if (ph.getElementsByClassName(`${har[i]}`)[0].checked==true){
        binn[i]=1; 
      }else{
        binn[i]=0; 
      }
    }
    for (i=0;i<7;i++){
      if (ph1.getElementsByClassName(`${har[i]}`)[0].checked==true){
        binn1[i]=1; 
      }else{
        binn1[i]=0; 
      }
    }
    // for (i=0;i<7;i++){
    //   if (ph2.getElementsByClassName(`${har[i]}`)[0].checked==true){
    //     binn2[i]=1; 
    //   }else{
    //     binn2[i]=0; 
    //   }
    // }
    // for (i=0;i<7;i++){
    //   if (ph3.getElementsByClassName(`${har[i]}`)[0].checked==true){
    //     binn3[i]=1; 
    //   }else{
    //     binn3[i]=0; 
    //   }
    // }
    // for (i=0;i<7;i++){
    //   if (ph4.getElementsByClassName(`${har[i]}`)[0].checked==true){
    //     binn4[i]=1; 
    //   }else{
    //     binn4[i]=0; 
    //   }
    // }
   
    var integerh = parseInt(binn.join(""), 2);  //merubah jadi integer
    var integer1h = parseInt(binn1.join(""), 2); 
    // var integer2 = parseInt(binn2.join(""),2); 
    // var integer3 = parseInt(binn3.join(""),2); 
    // var integer4 = parseInt(binn4.join(""),2); 

    let x = document.getElementById("sembunyih");
    x.value=integerh;
    let x1 = document.getElementById("sembunyi1h");
    x1.value=integer1h;
    // let x2 = document.getElementById("sembunyi2");
    // x2.value=integer2;
    // let x3 = document.getElementById("sembunyi3");
    // x3.value=integer3;
    // let x4 = document.getElementById("sembunyi4");
    // x4.value=integer4;
   
  }


  function kirimAH1(){
  }

  function kirimAhReal(){
    let kirim=document.getElementById("ngeluh2"); //gimana caranya dihilangkan setingan harinya??????
    kirim.submit(); //id ngeluh adalah id form
  }
    

//ini fungsi pengelolaan representasi hari dalam seminggu
function loopInInterval(angkadecimal, urut) {
var bine;
var situng;
bine = angkadecimal.toString(2); //merubah jadi bineer string
situng = bine.split(""); //merubah biner jadi array
let parr = situng.length;
   for (let i=0; i<(7-parr); i++) {
      situng.unshift("0");   //manambah arraynya dengan nool didepan karena arraynya tidak berdigit 7
    }
    const daftarhari=["Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"];
    let tulis="";
      situng.forEach(myFunction);
      function myFunction(item, index){
        let ph=document.getElementById(`pilihhar${urut}`);
        if (item==1){
          ph.getElementsByClassName(`${daftarhari[index]}`)[0].checked=true;
        }
        if (item != 0){  //awas..... ini angka atau string
          tulis += daftarhari[index] +" "; 
        }
    }
return tulis;
};

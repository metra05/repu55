


var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
  if (this.readyState == 4 && this.status == 200) {
    document.getElementById("teks1").innerHTML = this.responseText;
  }
};
xhttp.open("GET", "/teks1", true);
xhttp.send();


var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
  if (this.readyState == 4 && this.status == 200) {
    document.getElementById("teks2").innerHTML = this.responseText;
  }
};
xhttp.open("GET", "/teks2", true);
xhttp.send();


var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
  if (this.readyState == 4 && this.status == 200) {
    document.getElementById("teks3").innerHTML = this.responseText;
  }
};
xhttp.open("GET", "/teks3", true);
xhttp.send();
//}, 1000 ) ; //ini tes...........................................

// //menampilkan jam alarm
// var xhttp = new XMLHttpRequest();
// xhttp.onreadystatechange = function() {
//   if (this.readyState == 4 && this.status == 200) {
//     var alrmaray=this.responseText;
//     var myarray= alrmaray.split(" ");
//     document.getElementById("alarm").innerHTML = myarray[0] + " : "+myarray[1] + " Selama: " + myarray[2]+ ", int:" + myarray[4];//this.responseText;
//     document.getElementById("alarmjam").value = myarray[0];
//     document.getElementById("alarmmenit").value = myarray[1];
//     document.getElementById("alarmdetik").value = myarray[2];
//     if (myarray[3]==1){ 
//       document.getElementById("aktif1").checked=true;
//     }else {
//       document.getElementById("aktif1").checked=false;
//     }
//     var bin = loopInInterval(+myarray[4], "1");
//     document.getElementById("alarm2").innerHTML = bin;  //ini menampilkan hari
//     document.getElementById("sembunyi").value = myarray[4];
//   }
// };
// xhttp.open("GET", "/alarm", true);
// xhttp.send();


//menampilkan setingan hari-hari (alarm2)

setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        var angka = this.responseText;
        document.getElementById("alarm2").innerHTML = angka;  //ini menampilkan hari chek lagi!!!!!
      };
    };
    xhttp.open("GET", "/alarm2", true);
    xhttp.send();
}, 1000 ) ;



// function kirimAH(){
//   let binn=[];
//   let har=["Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"];
//   let ph=document.getElementById("pilihhar1");
//   for (i=0;i<7;i++){    //menyusun nilai binernya
//     if (ph.getElementsByClassName(`${har[i]}`)[0].checked==true){
//       binn[i]=1; 
//     }else{
//       binn[i]=0; 
//     }
//   }
//   var integer = parseInt(binn.join(""), 2);  //merubah jadi integer
//   let x = document.getElementById("sembunyi");
//   x.value=integer;
// }


function kirimAhReal(){
  let kirim=document.getElementById("ngeluh"); //gimana caranya dihilangkan setingan harinya??????
  //console.log(kirim);
  kirim.submit(); //id ngeluh adalah id form
}
      

// //ini fungsi pengelolaan representasi hari dalam seminggu
// function loopInInterval(angkadecimal, urut) {
//   var bine;
//   var situng;
//   bine = angkadecimal.toString(2); //merubah jadi bineer string
//   situng = bine.split(""); //merubah biner jadi array
//   let parr = situng.length;
//      for (let i=0; i<(7-parr); i++) {
//         situng.unshift("0");   //manambah arraynya dengan nool didepan karena arraynya tidak berdigit 7
//       }
//       const daftarhari=["Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"];
//       let tulis="";
//         situng.forEach(myFunction);
//         function myFunction(item, index){
//           let ph=document.getElementById(`pilihhar${urut}`);
//           if (item==1){
//             ph.getElementsByClassName(`${daftarhari[index]}`)[0].checked=true;
//           }
//           if (item != 0){  //awas..... ini angka atau string
//             tulis += daftarhari[index] +" "; 
//           }
//       }
//   return tulis;
// };




var slider = document.getElementById("kecerahan");
var output = document.getElementById("valuecerah");
output.innerHTML = slider.value;
slider.oninput = function() {
  output.innerHTML = this.value;
  // var xhttp = new XMLHttpRequest();
  //   xhttp.onreadystatechange = function() {
  //     if (this.readyState == 4 && this.status == 200) {
  //       var angka = this.responseText;
  //       document.getElementById("cerah").innerHTML = angka;  //ini menampilkan hari
  //     };
  //   };
  //   xhttp.open("GET", "/cerah", true);
  //   xhttp.send();
}

var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
  if (this.readyState == 4 && this.status == 200) {
    var angka = this.responseText;
    document.getElementById("valuecerah").innerHTML = angka;  //ini menampilkan hari
    document.getElementById("kecerahan").value = +angka;
    // output.innerHTML = +angka;
  };
};
xhttp.open("GET", "/cerah", true);
xhttp.send();


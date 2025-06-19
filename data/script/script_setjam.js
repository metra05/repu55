/////////////////////////////////////////////////////////////////////////////////////////////

  setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("jam").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/jam", true);
    xhttp.send();
  }, 1000 ) ;

  setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("tanggal").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/tanggal", true);
    xhttp.send();
  }, 1000 ) ;

  setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("hari").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/hari", true);
    xhttp.send();
  }, 1000 ) ;

  

  /////////////////////////////////////////////////////////////////////////////
  //sinkron
    function sinkron() {
     // alert();
      const d = new Date();
      let detik = d.getSeconds(); //ini tidak dikirim
      let menit = d.getMinutes();
      let jam = d.getHours();
      let tahun = d.getFullYear();
      let bulan = 1 + d.getMonth();
      let tanggal = d.getDate();
      let hari = d.getDay();

      //console.log(detik +" "+ menit +" "+ jam +" "+ tahun +" "+ bulan +" "+ tanggal +" "+ hari );
      let submit = `/get?nama=${tahun}&bulan=${bulan}&tanggal=${tanggal}&jam=${jam}&menit=${menit}&detik=${detik}&hari=${hari}`
      var xhttp = new XMLHttpRequest();
      
      xhttp.onreadystatechange = function() { 
        if (xhttp.readyState == 4 && xhttp.status == 200)
            callback(xhttp.responseText);
      }
      xhttp.open("GET", submit, true);
      xhttp.send();
      
      //console.log(submit);
      //
    }

  ///////////////////////////////////////////////////////////////////////////////
  



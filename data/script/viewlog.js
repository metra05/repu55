let container = document.getElementById('data-containerlog');

setInterval(function ( ) {
 var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        //document.getElementById("state").innerHTML = this.responseText;
        container.innerHTML = this.responseText;
        console.log(this.responseText);
       };
    };
    xhttp.open("GET", "/viewl", true);
    xhttp.send();
  }, 20000 ) ;
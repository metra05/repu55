// var xhttp = new XMLHttpRequest();
// xhttp.onreadystatechange = function() {
//   if (this.readyState == 4 && this.status == 200) {
//     document.getElementById("hasil").innerHTML = this.responseText;
//   }
// };
// xhttp.open("GET", "/hasil", true);
// xhttp.send();


function scanWiFi() {
  fetch('/scan')
    .then(response => response.json())
    .then(data => {
      let list = document.getElementById('wifiList');
      list.innerHTML = '';
      data.forEach(ap => {
        let li = document.createElement('li');
        li.textContent = ap.ssid + ' (RSSI: ' + ap.rssi + ')';
        list.appendChild(li);
      });
    });
}
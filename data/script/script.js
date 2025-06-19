// =================================================================================
  //membuat data dalam bentuk data objek
  
  let data={};
  data={temp:{current:0,high:0,low:100}};

  var temperature = new DonutChart();
  temperature.setSensorDomain([0,30]);//-6,50]);
  temperature.setSvgDiv('#donut1');
  temperature.createChart('\u00B0'+"dt", "detik");

  function waktu() {setInterval(() => {
              data.temp.current=data.temp.current+1
              temperature.updateChart(data.temp.current);
              // console.log(data);
              if (data.temp.current>=60){
                  data.temp.current=-1;
              };
      }, 1000);
  }

  waktu();
  
/////////////////////////////////////////////////////////////////////////////////////////////

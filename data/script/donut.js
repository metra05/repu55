var DonutChart = function(){
    var pi = Math.PI;
    var sensorDomainArray;
    var divIdName;
    var sensorAmount;
    var sensorText = "";
    var sensorScale;
    var foreground;
    var jarum;
    var arc;
    var svg;
    var g;
    var textValue;
    var textlow ="";
    var textHigh ="";
    let warna="";
    
    function setSensorDomain(domainArray){
        sensorDomainArray = domainArray;
    };

    function setSvgDiv(name){
        divIdName = name;
    };

    function createChart(sensorTextNew, sensorType){
        sensorText = sensorTextNew;
        var margin = {top: 10, right: 10, bottom: 10, left: 10};
        var width = 395 - margin.left - margin.right;   //ukuran wadah(svg)
        var height = 300;
        sensorScale = d3.scaleLinear()
            .range([0, 180]);       
        arc = d3.arc()              //ukuran donut
            .innerRadius(140)
            .outerRadius(150)
            .startAngle(0);

        svg = d3.select(divIdName).append("svg")    //d3 menyelect tag berdasarkan id
            .attr("width", width + margin.left + margin.right)
            .attr("height", height + margin.top + margin.bottom);

        g = svg.append("g").attr("transform", "translate(" + width / 2 + "," + height / 2 + ")");
        l = svg.append("g").attr("transform", "translate(" + width / 2 + "," + height / 2 + ")");
        l1 = svg.append("g").attr("transform", "translate(" + width / 2 + "," + height / 2 + ")");
        l2 = svg.append("g").attr("transform", "translate(" + width / 2 + "," + height / 2 + ")");

        g.append("text")
            .attr("text-anchor", "middle")
            .attr("font-size", "1em")
            .attr("y", -90)
            .attr("x",0)
            .text(sensorDomainArray[0]);
        g.append("text")
            .attr("text-anchor", "middle")
            .attr("font-size", "1em")
            .attr("y", 100)
            .attr("x",0)
            .text(sensorDomainArray[1]);
        g.append("text")
            .attr("text-anchor", "middle")
            .attr("font-size", "1.3em")
            .attr("y", 50)
            .text("detik")//sensorType);
        textValue = g.append("text")
            .attr("text-anchor", "middle")
            .attr('font-size', '1.8em')
            .attr('y', 75)
            .text(sensorAmount + "dt" )//+ sensorText);
        var background = g.append("path")
            .datum({endAngle: 2*pi})
            .style("fill", "#ddd")
            .attr("d", arc)
            //.attr("transform", "rotate(-90)")
        foreground = g.append("path")
            .datum({endAngle: pi})
            .style("fill", "#FE8402")
            .attr("d", arc)
           // .attr("transform", "rotate(-90)");

        //ini tick..........................................
        let det2=[0,1,2,3,4,5,6,7,8,9,10,11];
        let det=[0,1,2,3];
        l1.selectAll("line")
            .data(det)
            .enter()
            .append("line")
            .style("stroke", "black")
            .style("stroke-width", 1)
            .attr("x1", -105).attr("y1", 0)
            .attr("x2", -130).attr("y2", 0)
            .attr("transform", d=>"rotate("+d*180/2+")"); 

        l2.selectAll("line")
            .data(det2)
            .enter()
            .append("line")
            .style("stroke", "black")
            .style("stroke-width", 1)
            .attr("x1", -115).attr("y1", 0)
            .attr("x2", -130).attr("y2", 0)
            // .attr("x1", -120).attr("y1", 0)
            // .attr("x2", -130).attr("y2", 0)
            .attr("transform", d=>"rotate("+d*180/6+")"); 
        
        let det3=[];                    //membuat tik yang paling kecil 
        for (let i=0; i<60; i++){
            if (i%5!=0){
                det3.push(i);
            }
        }
        //console.log(sensorDomainArray[1]*180);
        console.log(det3);

        l.selectAll("line")
            .data(det3)
            .enter()
            .append("line") 
            .style("stroke", "black")
            .style("stroke-width", 1)
            .attr("x1", -123).attr("y1", 0)
            .attr("x2", -130).attr("y2", 0)
            .attr("transform", d=>"rotate("+d*180/30+")"); 

        ////////////////////////////////////ini jarum jam
        jarumJ = l.append("line")
        .style("stroke", "black")
        .style("stroke-width", 7)
        .attr("x1", 0)
        .attr("y1", 0)
        .attr("x2", 0)
        .attr("y2", -65);

        ///////////////////////////////////ini jarum menit
        jarumM = l.append("line")
        .style("stroke", "black")
        .style("stroke-width", 5)
        .attr("x1", 0)
        .attr("y1", 0)
        .attr("x2", 0)
        .attr("y2", -85);

        ///////////////////////////////////////ini jarum detik
        l.append('circle')
            .attr("fill","red")
            .attr("r","10");
        l.append('circle')    
            .attr("fill","black")
            .attr("r","5");
        jarum = l.append("line")
            .style("stroke", "black")
            .style("stroke-width", 3)
            .attr("x1", 0)
            .attr("y1", 0)
            .attr("x2", 0)
            .attr("y2", -100);
        ekor = l.append("line")
            .style("stroke", "black")
            .style("stroke-width", 2)
            .attr("x1", 0)
            .attr("y1", 0)
            .attr("x2", 0)
            .attr("y2", 30);
    }

    function updateChart(newSensorValue){
        const d = new Date();
        let detik = d.getSeconds();
        let newScaleD=d3.scaleLinear()
                .domain([0,60])
                .range([0,360]); 
        detik2=newScaleD(detik); 
        
        sensorScale.domain(sensorDomainArray);
        var sensorValue = sensorScale(newSensorValue);
        sensorValue = sensorValue/180;
        //textValue.text(newSensorValue + "" + sensorText);
        textValue.text(detik + "" + sensorText);
        //console.log(sensorValue*pi);
        let newCol=d3.scaleLinear()
            .domain([0,1])
            .range(["blue","red"]);

        warna=newCol(detik2/360);//sensorValue);
        //console.log(warna);

        foreground.transition()
            .duration(550)
            .style("fill", warna)
            //.attrTween("d", arcAnimation(sensorValue * pi));        
            .attrTween("d", arcAnimation(detik2/180*pi));

        jarum.transition()
            .duration(550)
            //.attr("transform", "rotate("+sensorValue*180+")"); //${sensorValue*pi})`);   .attr("transform", "rotate(40)")
            .attr("transform", "rotate("+detik2+")");
        ekor.transition()
            .duration(550)
            //.attr("transform", "rotate("+sensorValue*180+")"); 
            .attr("transform", "rotate("+detik2+")");

        let hour = d.getHours();
        let newScaleJ=d3.scaleLinear()
                .domain([0,12])
                .range([0,360]);
        hour2=newScaleJ(hour);
        jarumJ.transition()
                .duration(750)
                .attr("transform", "rotate("+hour2+")");
        //console.log(hour);
        //console.log(hour2);

        let minute =d.getMinutes(); 
        let newScaleM=d3.scaleLinear()
                .domain([0,60])
                .range([0,360]); 
        minute2=newScaleM(minute);  
        jarumM.transition()
            .duration(750)
            .attr("transform", "rotate("+minute2+")");
    }

    function arcAnimation(newAngle){
        return function(d) {
            var interpolate = d3.interpolate(d.endAngle, newAngle);
            return function(t) {
                d.endAngle = interpolate(t);
                return arc(d);
            };
        };
    }

    return{
        setSensorDomain: setSensorDomain,
        setSvgDiv: setSvgDiv,
        createChart:createChart,
        updateChart: updateChart
    }
 
};
        

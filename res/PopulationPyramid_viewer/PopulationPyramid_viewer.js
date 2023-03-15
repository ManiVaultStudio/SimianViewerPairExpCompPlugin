//global Variables
var _data = null;
var flag = false;
var _dataQueue = new PopulationPyramidViewerDataQueue(1, queueData);
var _defaultValues = null;
var yAxisLeftTooltip;
window.onresize = doALoadOfStuff;
var numOFBars;
var maxValue;
var screenHeight;
var screenWidth;
var svg;
var tooltip;
var barspace = 5;
var chartHeight;
var chartWidth;
var containerHeight
var yScaleTooltip;
var pointATooltip;
var pointBTooltip;
var xScaleTooltip;
var species1Name = "";
var species2Name = "";
var selectioncolor = "#257afd";
var geneName = "";
var selectedCrossspeciescluster = "";
var ClusterStorage1 = {};
var ClusterStorage2 = {};
const sortingCrossSpeciesClustersList = ["Lamp5_1", "Lamp5_2", "Lamp5_Lhx6_1", "Sncg_1", "Sncg_2", "Sncg_3", "Vip_1", "Vip_2", "Vip_3", "Vip_4", "Vip_5", "Vip_6", "Vip_7", "Vip_8", "Pax6_1", "Pax6_2","Sst Chodl_1", "Sst_1", "Sst_2", "Sst_3", "Sst_4", "Sst_5", "Sst_6", "Sst_7", "Sst_8", "Sst_9", "Pvalb_1", "Pvalb_2", "Pvalb_3", "Pvalb_4", "Chandelier_1","L2/3 IT_1", "L2/3 IT_2", "L2/3 IT_3", "L4 IT_1", "L4 IT_2", "L5 IT_1", "L5 IT_2", "L6 IT Car3_1", "L6 IT Car3_2", "L6 IT_1", "Astro_1", "Oligo_1", "VLMC_1", "Endo_1", "Micro-PVM_1", "OPC_1", "OPC_2", "L6 CT_1", "L6 CT_2", "L6b_1", "L6b_2", "L6b_3", "L5 ET_1", "L5 ET_2", "L5/6 NP_1", "L5/6 NP_2"];
//Qt Connections
try {
    new QWebChannel(qt.webChannelTransport, function (channel) {
        QtBridge = channel.objects.QtBridge;
        QtBridge.qt_setData.connect(function () { setData(arguments[0]); });
        QtBridge.qt_updateSelectionColor.connect(function () { updateSelectionColor(arguments[0]); });
        QtBridge.qt_setSelectedCrossspeciescluster.connect(function () { setSelectedCrossspeciescluster(arguments[0]); });
        notifyBridgeAvailable();
    });
} catch (error) { isQtAvailable = false; }

/*function mouseclickSpecies1(d) {
    //log("\Sending Species 1 cluster to QT from Javascript: " + d.clusterName);
    //svg.select("#mouseclickSpecies2").remove();
    svg.select("#mouseclickSpecies1").remove();
    svg.append('rect')
        .attr("id", "mouseclickSpecies1")
        .attr('x', pointATooltip - xScaleTooltip(d.species1ClusterCount))
        .attr('y', yScaleTooltip(d.clusterName))
        .attr('width', xScaleTooltip(d.species1ClusterCount))
        .attr('height', yScaleTooltip.bandwidth())
        .attr('stroke', selectioncolor)
        .attr("stroke-width", 2)
        .attr('fill', 'none');

    if (isQtAvailable) {
        QtBridge.js_passSelectionSpecies1ToQt(d.clusterName);
    }
}

function mouseclickSpecies2(d) {
    //log("\Sending Species 2 cluster to QT from Javascript: " + d.clusterName);
    svg.select("#mouseclickSpecies2").remove();
   // svg.select("#mouseclickSpecies1").remove();
    svg.append('rect')
        .attr("id","mouseclickSpecies2")
        .attr('x', pointBTooltip)
        .attr('y', yScaleTooltip(d.clusterName))
        .attr('width', xScaleTooltip(d.species2ClusterCount))
        .attr('height', yScaleTooltip.bandwidth())
        .attr('stroke', selectioncolor)
        .attr("stroke-width", 2)
        .attr('fill', 'none');



    if (isQtAvailable) {
        QtBridge.js_passSelectionSpecies2ToQt(d.clusterName);
    }
}

//mouseclickBoth

function mouseclickBoth(d) {
    //log("\Sending both species clusters to QT from Javascript: " + d);
    svg.select("#mouseclickSpecies2").remove();
    svg.select("#mouseclickSpecies1").remove();
    svg.append('rect')
        .attr("id", "mouseclickSpecies1")
        .attr('x', pointATooltip - xScaleTooltip(ClusterStorage1[d]))
        .attr('y', yScaleTooltip(d))
        .attr('width', xScaleTooltip(ClusterStorage1[d]))
        .attr('height', yScaleTooltip.bandwidth())
        .attr('stroke', selectioncolor)
        .attr("stroke-width", 2)
        .attr('fill', 'none');


    svg.append('rect')
        .attr("id", "mouseclickSpecies2")
        .attr('x', pointBTooltip)
        .attr('y', yScaleTooltip(d))
        .attr('width', xScaleTooltip(ClusterStorage2[d]))
        .attr('height', yScaleTooltip.bandwidth())
        .attr('stroke', selectioncolor)
        .attr("stroke-width", 2)
        .attr('fill', 'none');

    if (isQtAvailable) {
        QtBridge.js_passSelectionSpecies1ToQt(d);
        QtBridge.js_passSelectionSpecies2ToQt(d);
    }
}*/
function clickMiddleLabel(d) {

    if (selectedCrossspeciescluster == d) {
        selectedCrossspeciescluster = "";
        if (document.querySelector('#mouseclickSpecies2') && svg) {
            svg.select("#mouseclickSpecies2").remove();
        }
        if (document.querySelector('#mouseclickSpecies1') && svg) {
            svg.select("#mouseclickSpecies1").remove();
        }

        svg
            .call(yAxisLeftTooltip)
            .selectAll("text")
            .style("fill", "black");
        if (isQtAvailable) {
            QtBridge.js_crossspeciesclusterSelection("");
        }
    }
    else {
        selectedCrossspeciescluster = d;
        selectBars(selectedCrossspeciescluster);
        QtBridge.js_crossspeciesclusterSelection(selectedCrossspeciescluster);
    }
}

function clickBar(d) {

    if (selectedCrossspeciescluster == d.clusterName) {
        selectedCrossspeciescluster = "";
        if (document.querySelector('#mouseclickSpecies2') && svg) {
            svg.select("#mouseclickSpecies2").remove();
        }
        if (document.querySelector('#mouseclickSpecies1') && svg) {
            svg.select("#mouseclickSpecies1").remove();
        }

        svg
            .call(yAxisLeftTooltip)
            .selectAll("text")
            .style("fill", "black");
        if (isQtAvailable) {
            QtBridge.js_crossspeciesclusterSelection("");
        }
    }
    else {
        selectedCrossspeciescluster = d.clusterName;
        selectBars(selectedCrossspeciescluster);
        QtBridge.js_crossspeciesclusterSelection(selectedCrossspeciescluster);
    }
}

function selectBars(d) {
    if (document.querySelector('#mouseclickSpecies2') && svg) {
        svg.select("#mouseclickSpecies2").remove();
    }
    if (document.querySelector('#mouseclickSpecies1') && svg) {
        svg.select("#mouseclickSpecies1").remove();
    }

    svg
        .call(yAxisLeftTooltip)
        .selectAll("text")
        .style("fill", "black");

    svg.append('rect')
        .attr("id", "mouseclickSpecies1")
        .attr('x', pointATooltip - xScaleTooltip(ClusterStorage1[d]))
        .attr('y', yScaleTooltip(d))
        .attr('width', xScaleTooltip(ClusterStorage1[d]))
        .attr('height', yScaleTooltip.bandwidth())
        .attr('stroke', selectioncolor)
        .attr("stroke-width", 2)
        .attr('fill', 'none');


    svg.append('rect')
        .attr("id", "mouseclickSpecies2")
        .attr('x', pointBTooltip)
        .attr('y', yScaleTooltip(d))
        .attr('width', xScaleTooltip(ClusterStorage2[d]))
        .attr('height', yScaleTooltip.bandwidth())
        .attr('stroke', selectioncolor)
        .attr("stroke-width", 2)
        .attr('fill', 'none');

    svg
        .call(yAxisLeftTooltip)
        .selectAll("text")
        .style("fill", function (m) {
            if (m == d) {
                return selectioncolor;
            }
            else {
                return "black";
            }
        });



    if (yScaleTooltip(d) > 1) {
        window.scrollTo(0, yScaleTooltip(d) -1);
        }
        else {
        window.scrollTo(0, yScaleTooltip(d));
        }
}


/*function mouseenterSpecies(d) {

}*/
function mouseleaveSpecies(d) {
    tooltip
        .style("opacity", 0)
}
function mousemoveSpecies(d) {
    tooltip.style("position", "absolute");

    if (d3.event.pageX > window.innerWidth / 2) {
        tooltip
            .style('left', (d3.event.pageX - 30) + 'px')
    }
    else {
        tooltip
            .style('left', (d3.event.pageX + 30) + 'px')
    }
    var temp;
    if (containerHeight / 2 > window.innerHeight / 2) {
        temp = containerHeight / 2;
    }
    else {
        temp = window.innerHeight / 2;
    }
    
    if (d3.event.pageY >= temp / 2) {
        tooltip
            .style('top', (d3.event.pageY - 30) + 'px')
    }
    else {
        tooltip
            .style('top', (d3.event.pageY + 30) + 'px')
    }

}
/*function mouseoutSpecies(d) {

}*/
function mouseoverSpecies1(d) {
    tooltip
        .html("<div><b>" + d.species1ClusterCount+"</b></div>")
        .style("opacity", 1)
}

function mouseoverSpecies2(d) {
    tooltip
        .html("<div><b>" + d.species2ClusterCount + "</b></div>")
        .style("opacity", 1)
}

//Main Visualization
const PopulationPyramidVis = () => {
    d3.select("g").remove();
    d3.select("svg").remove();
    svg = d3.select("#my_dataviz");
    svg.selectAll("*").remove();
    svg_Axes = d3.select("#my_dataviz_axes");
    svg_Axes.selectAll("*").remove();

    //var exampleDataTooltip = [
    //    { clusterName: "L5 IT/3", species1ClusterCount: 10, species2ClusterCount: 20, clusterColor: "red"},
    //    { clusterName: "2", species1ClusterCount: 30, species2ClusterCount: 40 ,clusterColor:"red"},
    //    { clusterName: "3", species1ClusterCount: 50, species2ClusterCount: 60, clusterColor: "blue"},
    //    { clusterName: "4", species1ClusterCount: 70, species2ClusterCount: 90, clusterColor: "green"},
    //    { clusterName: "5", species1ClusterCount: 80, species2ClusterCount: 70, clusterColor: "yellow" },
    //    { clusterName: "6", species1ClusterCount: 60, species2ClusterCount: 50, clusterColor: "purple" },
    //    { clusterName: "7", species1ClusterCount: 10, species2ClusterCount: 20, clusterColor: "pink" },
    //    { clusterName: "8", species1ClusterCount: 30, species2ClusterCount: 40, clusterColor: "green"},
    //    { clusterName: "9", species1ClusterCount: 50, species2ClusterCount: 60, clusterColor: "violet" },
    //    { clusterName: "10", species1ClusterCount: 70, species2ClusterCount: 90, clusterColor: "black" },
    //    { clusterName: "11", species1ClusterCount: 80, species2ClusterCount: 70, clusterColor: "orange"},
    //    { clusterName: "12", species1ClusterCount: 60, species2ClusterCount: 50, clusterColor: "red"},
    //    { clusterName: "0", species1ClusterCount: 60, species2ClusterCount: 50, clusterColor: "red"},
    //];
    var numOFBars = _data.length;

    containerHeight = numOFBars * 20;
    var marginTooltip = {
        topTooltip: 5,
        rightTooltip: 5,
        bottomTooltip: 1,
        leftTooltip: 5,
        middleTooltip: 80,
    };//middle space
    var wTooltip = (90 / 100) * window.innerWidth;
    var hTooltip =
        containerHeight + marginTooltip.topTooltip + marginTooltip.bottomTooltip;
    var regionWidthTooltip =
        (wTooltip -
            marginTooltip.rightTooltip -
            marginTooltip.leftTooltip -
            marginTooltip.middleTooltip) /
        2;
     pointATooltip = regionWidthTooltip;
        pointBTooltip = wTooltip - regionWidthTooltip;

     svg = d3
        .select("#my_dataviz")
        .append("svg")
        .attr(
            "width",
            marginTooltip.leftTooltip + wTooltip + marginTooltip.rightTooltip
        )
        .attr(
            "height",
            marginTooltip.topTooltip + hTooltip + marginTooltip.bottomTooltip
        )
        .append("g")
        .attr(
            "transform",
            translation(marginTooltip.leftTooltip, marginTooltip.topTooltip)
    );

    tooltip = d3.select("#my_dataviz")
        .append("div")
        .style("opacity", 0)
        .attr("class", "tooltip")
        .style("background-color", "white")
        .style("border", "solid")
        .style("border-width", "1px")
        .style("border-radius", "5px");
    var maxValueTooltip = Math.max(
        d3.max(_data, function (d) {
            return d.species1ClusterCount;
        }),
        d3.max(_data, function (d) {
            return d.species2ClusterCount;
        })
    );
     xScaleTooltip = d3
        .scaleLinear()
        .domain([0, maxValueTooltip])
        .range([0, regionWidthTooltip])
        .nice();
    //var xScaleLeftTooltip = d3
    //    .scaleLinear()
    //    .domain([0, maxValueTooltip])
    //    .range([regionWidthTooltip, 0]);
    //var xScaleRightTooltip = d3
    //    .scaleLinear()
    //    .domain([0, maxValueTooltip])
    //    .range([0, regionWidthTooltip]);
     yScaleTooltip = d3
        .scaleBand()
        .domain(
            _data.map(function (d) {
                return d.clusterName;
            })
        )
        .rangeRound([hTooltip, 0])
        .padding(0.1);
     yAxisLeftTooltip = d3
        .axisRight()
        .scale(yScaleTooltip)
        .tickSize(4, 0)
        .tickPadding(marginTooltip.middleTooltip - 40);///middlespace
    var yAxisRightTooltip = d3
        .axisLeft()
        .scale(yScaleTooltip)
        .tickSize(4, 0)
        .tickFormat("");

    var leftBarGroupTooltip = svg
        .append("g")
        .attr("transform", translation(pointATooltip, 0) + "scale(-1,1)");
    var rightBarGroupTooltip = svg
        .append("g")
        .attr("transform", translation(pointBTooltip, 0));
    svg
        .append("g")
        .attr("class", "axis y left")
        .attr("transform", translation(pointATooltip, 0))
        .call(yAxisLeftTooltip)
        .selectAll("text")
        .on("click", clickMiddleLabel)
        .attr("shape-rendering", "crispEdges")      
        .style("cursor", "pointer")
        //.attr("fill", "transparent")
        .attr("fill", "black")
        .attr("font-size", "10").style("font-family", "Arial")
        //.attr("stroke", "#000000")
        .style("text-anchor", "middle");
    svg
        .append("g")
        .attr("class", "axis y right")
        .attr("transform", translation(pointBTooltip, 0))
        //.on("click", mouseclickBoth)
        .attr("shape-rendering", "crispEdges")
        //.attr("fill", "transparent")
        //.attr("stroke", "#000000")
        .attr("fill", "black")
        .attr("font-size", "10").style("font-family", "Arial")
        .call(yAxisRightTooltip);

    leftBarGroupTooltip
        .selectAll(".bar.left")
        .data(_data)
        .enter()
        .append("rect")
        .attr("class", "bar left")
        .attr("x", 0)
        .attr("y", function (d) {
            return yScaleTooltip(d.clusterName);
        })
        .attr("width", function (d) {
            return xScaleTooltip(d.species1ClusterCount);
        })
        .attr("fill", function (d) {
            return d.clusterColor;
        })
/*        .attr("stroke", function (d) {
            if (d.clusterName == selectedCrossspeciescluster) { return selectioncolor; }
            else { "none" }
        })
        .attr("stroke-width", function (d) {
            if (d.clusterName == selectedCrossspeciescluster) { return 3; }
        })*/
        .attr("height", yScaleTooltip.bandwidth())
        .on("click", clickBar)
        .style("cursor", "pointer")
        .on("mouseover", mouseoverSpecies1)
        //.on("mouseout", mouseoutSpecies)
        .on("mousemove", mousemoveSpecies)
        .on("mouseleave", mouseleaveSpecies)
        //.on("mouseenter", mouseenterSpecies)
        //.on("click", mouseclickSpecies1)
        ;
    rightBarGroupTooltip
        .selectAll(".bar.right")
        .data(_data)
        .enter()
        .append("rect")
        .attr("class", "bar right")
        .attr("x", 0)
        .attr("y", function (d) {
            return yScaleTooltip(d.clusterName);
        })
        .attr("width", function (d) {
            return xScaleTooltip(d.species2ClusterCount);
        })
        .attr("fill", function (d) {
            return d.clusterColor;
        })
/*        .attr("stroke", function (d) {
            if (d.clusterName == selectedCrossspeciescluster) { return selectioncolor; }
            else { "none" }
        })
        .attr("stroke-width", function (d) {
            if (d.clusterName == selectedCrossspeciescluster) { return 3; }
        })*/
        .attr("height", yScaleTooltip.bandwidth())
        .style("cursor", "pointer")
        .on("click", clickBar)
        .on("mouseover", mouseoverSpecies2)
        //.on("mouseout", mouseoutSpecies)
        .on("mousemove", mousemoveSpecies)
        .on("mouseleave", mouseleaveSpecies)
        //.on("mouseenter", mouseenterSpecies)
        //.on("click", mouseclickSpecies2)
        ;
    function translation(x, y) {
        return "translate(" + x + "," + y + ")";
    }

    var svgAxis = d3
        .select("#my_dataviz_axes")
        .append("svg")
        .attr(
            "width",
            marginTooltip.leftTooltip + wTooltip + marginTooltip.rightTooltip
        )
        .attr("height", 40)
        .append("g")
        .attr(
            "transform",
            translation(marginTooltip.leftTooltip, marginTooltip.topTooltip)
        );
    var maxValueTooltip = Math.max(
        d3.max(_data, function (d) {
            return d.species1ClusterCount;
        }),
        d3.max(_data, function (d) {
            return d.species2ClusterCount;
        })
    );

    var xAxisRightTooltip = d3.axisTop().scale(xScaleTooltip).ticks(2);
    var xAxisLeftTooltip = d3
        .axisTop()
        .scale(xScaleTooltip.copy().range([pointATooltip, 0 + 5]))
        .ticks(2);//tick
    svgAxis
        .append("g")
        .attr("class", "axis x left")
        .attr("transform", translationAxes(0, 12))
        .attr("shape-rendering", "crispEdges")
        //.attr("fill", "transparent")
        //.attr("stroke", "#3A3B3C")
        .attr("fill", "black")
        .call(xAxisLeftTooltip)
        .selectAll("text")
        .attr("dy", ".21em");
    svgAxis
        .append("g")
        .attr("class", "axis x right")
        .attr("transform", translationAxes(pointBTooltip, 12))
        .attr("shape-rendering", "crispEdges")
        //.attr("fill", "transparent")
        //.attr("stroke", "#3A3B3C")
        .attr("fill", "black")
        .call(xAxisRightTooltip)
        .selectAll("text")
        .attr("dy", ".21em");

    svgAxis
        .append("text")
        .attr("text-anchor", "middle")
        .attr("x", pointATooltip / 2)
        .attr("y", 26)
        .text(species1Name)
        .attr("font-size", "10").style("font-family", "Arial");

    svgAxis
        .append("text")
        .attr("text-anchor", "middle")
        .attr("x", pointBTooltip / 2 + pointBTooltip)
        .attr("y", 26)
        .text(species2Name)
        .attr("font-size", "10").style("font-family", "Arial");

    svgAxis
        .append("text")
        .attr("text-anchor", "middle")
        .attr("x", pointATooltip + (pointBTooltip - pointATooltip)/2)
        .attr("y", 27)
        .text(geneName)
        .attr("font-size", "10").style("font-family", "Arial");
    svgAxis
        .append("text")
        .attr("text-anchor", "middle")
        .attr("x", pointATooltip + (pointBTooltip - pointATooltip) / 2)
        .attr("y", 15)
        .text("Gene")
        .attr("font-size", "10").style("font-family", "Arial");

    svgAxis.selectAll(".tick").each(function (d) {
      if (d === 0.0 || d === 0) {
        this.remove();
      }
    });
    function translationAxes(x, y) {
        return "translate(" + x + "," + y + ")";
    }
    if (selectedCrossspeciescluster!=="") {
        selectBars(selectedCrossspeciescluster);
    }

};


/*function setBarhighlight(d) {




    if (d !== "" || d != null || d != undefined) {
        if (d in ClusterStorage1 && d in ClusterStorage2) {

        svg.select("#mouseclickSpecies2").remove();
        svg.select("#mouseclickSpecies1").remove();


        svg.append('rect')
            .attr("id", "mouseclickSpecies1")
            .attr('x', pointATooltip - xScaleTooltip(ClusterStorage1[d]))
            .attr('y', yScaleTooltip(d))
            .attr('width', xScaleTooltip(ClusterStorage1[d]))
            .attr('height', yScaleTooltip.bandwidth())
            .attr('stroke', selectioncolor)
            .attr("stroke-width", 2)
            .attr('fill', 'none');


        svg.append('rect')
            .attr("id", "mouseclickSpecies2")
            .attr('x', pointBTooltip)
            .attr('y', yScaleTooltip(d))
            .attr('width', xScaleTooltip(ClusterStorage2[d]))
            .attr('height', yScaleTooltip.bandwidth())
            .attr('stroke', selectioncolor)
            .attr("stroke-width", 2)
                .attr('fill', 'none');

            if (yScaleTooltip(d) > 1) {
                window.scrollTo(0, yScaleTooltip(d) - 1);
            }
            else {
                window.scrollTo(0, yScaleTooltip(d));
            }
    }

    }
}*/


//Data Options
function setData(d) {
    _dataQueue.addData(d);
    //log("\nReceived from QT to Javascript\n");
}

function setSelectedCrossspeciescluster(d) {
    if (d !== "") {
        selectedCrossspeciescluster = d;
        selectBars(selectedCrossspeciescluster);
    }
    else {
        selectedCrossspeciescluster = "";
            if (document.querySelector('#mouseclickSpecies2')&&svg) {
                svg.select("#mouseclickSpecies2").remove();
            }
        if (document.querySelector('#mouseclickSpecies1') && svg) {
            svg.select("#mouseclickSpecies1").remove();
        }
        
        
        svg
            .call(yAxisLeftTooltip)
            .selectAll("text")
            .style("fill", "black");
    }
}

function queueData(d) {
    _data = JSON.parse(d);
    //_data.sort(function (a, b) { var keyA = new Date(a.value), keyB = new Date(b.value); if (keyA > keyB) return -1; if (keyA < keyB) return 1; return 0; });
    //numOFBars = Object.keys(_data).length;
    for (var i = 0; i < _data.length; i++) {
        ClusterStorage1[_data[i].clusterName] = _data[i].species1ClusterCount;
        ClusterStorage2[_data[i].clusterName] = _data[i].species2ClusterCount;
    }

    _data.sort(function (a, b) {
        return sortingCrossSpeciesClustersList.indexOf(b.clusterName) - sortingCrossSpeciesClustersList.indexOf(a.clusterName)
    });

    species1Name = _data[0].species1Name;
    species2Name = _data[0].species2Name;
    geneName = _data[0].geneName;
    //maxValue = Object.keys(_data).reduce((acc, curr) => acc.value ? (_data[curr].value > acc.value ? _data[curr] : acc) : _data[curr], {});
    /*_data.sort(function (a, b) { return b.value - a.value; });*/
    PopulationPyramidVis();
    flag = true;
}

function updateSelectionColor(d) {
    var regex = /^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$/;
    if (regex.test(d)) {
        selectioncolor = d;
        PopulationPyramidVis();
    }

}

//Resize on window dimension change
function doALoadOfStuff() {
    if (flag) { PopulationPyramidVis(); }
}





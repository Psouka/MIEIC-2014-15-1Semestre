var dataVotes;
var dataAwnsers;

function drawChart(idQuery){
	$.getJSON("../db/countVotes.php", {'idQuery' : idQuery}, DataReceived);
}


function DataReceived(data){
	dataVotes = data;
	$.getJSON("../db/getAnswers.php", {'idQuery' : idQuery}, AwnsersReceived);
}

functionAwnsersReceived(data){
	dataAwnsers = data;
	drawC();
}

function  drawC() {
  var x = d3.scale.linear()
  .domain([0, d3.max(data)])
  .range([0, 420]);

  d3.select(".chart")
  .selectAll("div")
  .data(dataVotes)
  .enter().append("div")
  .style("width", function(d) { return x(d) + "px"; })
  .text(function(d) { return dataAwnsers[dataVotes.indexOf(d)]; });
}
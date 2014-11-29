var dataVotes;
var dataAwnsers;

var id;


function drawChart(idQuery){
  id = idQuery;
	$.getJSON("../db/countVotes.php", {'idQuery' : idQuery}, DataReceived);
}


function DataReceived(data){
  alert(data);
	dataVotes = data;
	$.getJSON("../db/getAnswers.php", {'idQuery' : id}, AwnsersReceived);
}

function AwnsersReceived(data){
  alert(data);
	dataAwnsers = data;
	drawC();
}

function  drawC() {
  var index = 0;
  var x = d3.scale.linear()
  .domain([0, d3.max(dataVotes)])
  .range([0, 420]);

  d3.select(".chart")
  .selectAll("div")
  .data(dataVotes)
  .enter().append("div")
  .style("width", function(d) { return x(d) + "px"; })
  .text(function(d) { return dataAwnsers[index++]; });
}
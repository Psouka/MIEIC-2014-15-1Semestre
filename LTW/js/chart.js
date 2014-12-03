var dataVotes;
var dataAwnsers;

var id;

var draw = 0;

function drawChart(idQuery){
  if(draw == 1)
    return;

  id = idQuery;
	$.getJSON("../db/countVotes.php", {'idQuery' : idQuery}, DataReceived);
}


function DataReceived(data){
	dataVotes = data;
	$.getJSON("../db/getAnswers.php", {'idQuery' : id}, AwnsersReceived);
}

function AwnsersReceived(data){
	dataAwnsers = data;
	drawC();
}

function  drawC() {
  draw = 1;
  var index = 0;
  var x = d3.scale.linear()
  .domain([0, d3.max(dataVotes)])
  .range([0, 375]);

  d3.select(".chart")
  .selectAll("div")
  .data(dataVotes)
  .enter().append("div")
  .style("width", function(d) { return x(d) + "px"; })
  .text(function(d) { return dataAwnsers[index++]; });
}
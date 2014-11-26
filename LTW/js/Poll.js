$(function() {
  // constants
  var SHOW_CLASS = 'show',
      HIDE_CLASS = 'hide',
      ACTIVE_CLASS = 'active';
  
  $( '.tabs' ).on( 'click', 'li a', function(e){
    e.preventDefault();
    var $tab = $( this ),
         href = $tab.attr( 'href' );
  
     $( '.active' ).removeClass( ACTIVE_CLASS );
     $tab.addClass( ACTIVE_CLASS );
  
     $( '.show' )
        .removeClass( SHOW_CLASS )
        .addClass( HIDE_CLASS )
        .hide();
    
      $(href)
        .removeClass( HIDE_CLASS )
        .addClass( SHOW_CLASS )
        .hide()
        .fadeIn( 550 );
  });
});

var bars;
var maxWidth = 500;
var maxFontSize = 60;

var px = function(i) { return i+"px"; };
var mult = function(a, b) { return a*b; };

var data1 = [
  {id: "Ola", value: 15},
  {id: 2, value:  2},
  {id: 4, value: 12},
  {id: 5, value: 20},
  {id: 7, value: 11},
  {id: 8, value: 10}];

var data2 = [
  {id: "Ola", value: 15},
  {id: 2, value: 11},
  {id: 3, value:  5},
  {id: 4, value: 19},
  {id: 5, value: 18},
  {id: 6, value:  3},
  {id: 7, value: 11}];

var dataMax = d3.max(d3.merge([data1, data2]), function (d) { return d.value; });
var ls = d3.scale.linear().domain([0, dataMax]);
var lsC = d3.scale.linear().domain([0, dataMax]).range(['#9cf', '#369']);


var lsWidth = function (d, i) { return px(mult(maxWidth, ls(d.value))); };
var lsFontSize = function (d, i) { return px(mult(maxFontSize, ls(d.value))); };
var lsColor = function (d, i) { return lsC(d.value); };


var d3Update = function (data) {

  bars = d3.select('#vis')
    .selectAll('.bar')
      .data(data, function (d, i) {
        return d.id;
      });

  bars.enter().append('div')
    .classed({'bar': true})
    .style('width', "0")
    .each(function (d, i) {
      d3.select(this).append('b').text(d.value);
      d3.select(this).append('i').text(d.id);
    });
  
  d3.select('#vis')
    .selectAll('.bar')
    .sort(function (d1, d2) {
    console.log(d1,d2);
    if (d1.id < d2.id) return -1;
    if (d1.id > d2.id) return +1;
    return 0;
  });
  
  bars.transition().duration(500)
      .style('width', lsWidth)
      .style('font-size', lsFontSize)
      .style('background-color', lsColor)
      .select('b')
      .text(function(d, i) { return d.value; });

  bars.exit().transition().duration(500)
    .style('width', function(d) { return "0px"; })
    .remove();
}

d3Update(data1);

var i = 0;
d3.select('button').on('click', function () {
  i++;
  d3Update(i%2==0?data1:data2);
});  


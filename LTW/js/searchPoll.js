
function addInput(Query,ID,divName){

var a;
var linkText;
for(var i = 0; i < ID.length; i++){
   
	a = document.createElement('a');
 linkText = document.createTextNode(Query);
a.appendChild(linkText);
a.title = Query;
a.href = "http://example.com";
document.getElementById(divName).appendChild(a);
}
     
}
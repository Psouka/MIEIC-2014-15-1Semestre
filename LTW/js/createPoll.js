
var counter = 1;
var limit = 6;
function addInput(divName){
     if (counter == limit)  {
          alert("You have reached the limit of adding " + counter + " inputs");
     }
     else {
          var newdiv = document.createElement('div');
          newdiv.innerHTML = "<input type='text' name='myInputs[]' placeholder='New Option.'>";
          document.getElementById(divName).appendChild(newdiv);
          counter++;
     }
}

var counter = 1;
var limit = 6;

function addInput(divName){
     if (counter == limit)  {
          alert("You reached the limit of " + counter + " optionerinos!");
     }
     else {
          var newdiv = document.createElement('div');
          newdiv.innerHTML = "<input type='text' name='inputs' placeholder='New Option.'> <input type='button' name='deleteInput' value='−'  required>";
          document.getElementById(divName).appendChild(newdiv);
          counter++;
     }
}

function deleteInput(divName) {

}

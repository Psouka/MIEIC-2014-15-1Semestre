
var counter = 3;
var limit = 7;

function addInput(divName){
     if (counter == limit)  {
          alert("You reached the limit of " + (counter-1) + " optionerinos!");
     }
     else {
          var newdiv = document.createElement('div');
          newdiv.setAttribute('class', 'addtinput');
          var nameA = "inputs" + counter.toString();
          var nameB = "deleteInput" + counter.toString();
          var nameC = 'onClick="deleteInput(this);"';
          newdiv.innerHTML = "<input type='text' name='" + nameA + "'class='newOpt' placeholder='New Optionerino...'> <input type='button' name='" 
          + nameB + "'class='buttonDel' value='−'" + nameC + ">";
          document.getElementById(divName).appendChild(newdiv);
          counter++;
     }
}

function deleteInput(divName) {
     var num = parseInt(divName.name.slice(-1));
     if(counter > 3) {
          divName.parentNode.parentNode.removeChild(divName.parentNode);
          counter--;
          var a = document.getElementsByClassName('addtinput');
          for(i = 0; i < counter - 1; i++) {
               var nameA = "inputs" + (i+1).toString();
               var nameB = "deleteInput" + (i+1).toString();
               a[i].getElementsByTagName('input')[0].setAttribute('name' , nameA);
               a[i].getElementsByTagName('input')[1].setAttribute('name' , nameB);
          }
     }
     else {
          alert("You have to have at least 2 optionerinos!")
     }
}

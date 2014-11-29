
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
          newdiv.innerHTML = "<input type='text' name='" + nameA + "'class='newOpt' placeholder='New Option...'> <input type='button' name='" 
          + nameB + "'class='buttonDel' value='−'" + nameC + ">";
          document.getElementById(divName).appendChild(newdiv);
          counter++;
     }
}

function deleteInput(divName) {
	var num = parseInt(divName.name.slice(-1));
	if(num > 2) {
		divName.parentNode.parentNode.removeChild(divName.parentNode);
          counter--;
          if(counter >= 3) {
               var a = document.getElementsByClassName('addtinput');
               for(i = 3; i < counter; i++) {
                    var nameA = "inputs" + i.toString();
                    var nameB = "deleteInput" + i.toString();
                    a[i-3].getElementsByTagName('input')[0].setAttribute('name' , nameA);
                    a[i-3].getElementsByTagName('input')[1].setAttribute('name' , nameB);
               }
          }
     }
}

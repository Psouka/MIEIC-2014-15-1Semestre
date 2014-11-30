var seeOptions = 0;


function showOptions(idQuery,username) {
	if(seeOptions == 0)
		$.getJSON("../db/getAnswers.php", {'idQuery' : idQuery}, OptionsReceived);
	else
		sendVote(idQuery,username)
}

function sendVote(idQuery,username){
	var rates =  document.getElementsByName('Vote');
	var OptionX= '';
	for(var i = 0; i < rates.length; i++){
		if(rates[i].checked){
			OptionX = rates[i].value;
			console.log(OptionX);
		}
	}
	if(OptionX == '')
	{
		alert('Select One');
		return;
	}
	$.post("../db/newVote.php", {'idQuery' : idQuery, 'OptionX' : OptionX , 'Username' : username}, registed);
	alert('Registed');

}

function registed(){
	console.log('Registado');

}

function  OptionsReceived(data) {
	$.each(data, resultOptions);
}

// Called for each line received
function resultOptions(index, value) {
	seeOptions = 1;
	var radioHtml = value +'<input type="radio" name="Vote"';
	radioHtml += 'value="' + value + '"'
	radioHtml += '/>';
	var radioFragment = document.createElement('div');
	radioFragment.innerHTML = radioHtml;

	document.getElementById('dynamicOptions').appendChild(radioFragment);
	return radioFragment.firstChild;
}

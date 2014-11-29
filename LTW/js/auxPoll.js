
function showOptions(idQuery) {
	$.getJSON("../db/getAnswers.php", {'idQuery' : idQuery}, OptionsReceived);
}


function  OptionsReceived(data) {
	alert(data);
	$.each(data, resultOptions);
}

// Called for each line received
function resultOptions(index, value) {
	
	var radioHtml = value +'<input type="radio" name="Vote"';
	radioHtml += 'value="' + value + '"'
	radioHtml += '/>';
	var radioFragment = document.createElement('div');
	radioFragment.innerHTML = radioHtml;

	document.getElementById('dynamicOptions').appendChild(radioFragment);
	return radioFragment.firstChild;
}

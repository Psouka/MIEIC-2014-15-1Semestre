
function showOptions(idQuery) {
	alert(idQuery);

	$.getJSON("../db/getAnswers.php", {'idQuery' : idQuery}, OptionsReceived);
}


function  OptionsReceived(data) {
	$.each(data, resultOptions);
}

// Called for each line received
function resultOptions(index, value) {
	alert('Option');
	var radioHtml = '<input type="radio" name="' + value + '"';
	radioHtml += '/>';

	var radioFragment = document.createElement('div');
	radioFragment.innerHTML = radioHtml;

	document.getElementById('dynamicSearch').appendChild(radioFragment);
	return radioFragment.firstChild;
}

function sendComment(idQuery, username){

	var comment =  document.getElementById("comment").value;
	
	if(comment.length < 7)
	{
		alert('Create a *Real* Comment');
		return;
	}

	$.post("../db/newCom.php", {'idQuery' : idQuery, 'Comment' : comment , 'Username' : username}, location.reload(true));
}
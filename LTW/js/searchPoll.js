    $(document).ready(function(){
        $('#results').html('<p>Enter a search term to start filtering.</p>');

        $('#word').keyup(function() {

            var searchVal = $(this).val();
            if(searchVal !== '') {
                $.get('../db/searchPoll.php?word='+searchVal, function(returnData) {
                    if (jQuery.isEmptyObject(searchVal)) {
                        $('#results').html('<p>Search term entered does not return any data.</p>');
                    } else {
                        $('#results').html(returnData);
                    }
                });
            } else {
                $('#results').html('<p>Enter a search term to start filtering.</p>');
            }

        });

        $('#id').keyup(function() {

            var searchVal = $(this).val();
            if(searchVal !== '') {
                $.get('../db/searchPoll.php?id='+searchVal, function(returnData) {
                   if (jQuery.isEmptyObject(searchVal)) {
                        $('#results').html('<p>Search term entered does not return any data.</p>');
                    } else {
                        $('#results').html(returnData);
                    }
                });
            } else {
                $('#results').html('<p>Enter a search term to start filtering.</p>');
            }

        });

        $('#username').keyup(function() {

            var searchVal = $(this).val();
            if(searchVal !== '') {
                $.get('../db/searchPoll.php?username='+searchVal, function(returnData) {
                    if (jQuery.isEmptyObject(searchVal)) {
                        $('#results').html('<p>Search term entered does not return any data.</p>');
                    } else {
                        $('#results').html(returnData);
                    }
                });
            } else {
                $('#results').html('<p>Enter a search term to start filtering.</p>');
            }

        });

    });
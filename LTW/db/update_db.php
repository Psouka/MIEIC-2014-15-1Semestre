<?php
  $db = new PDO('sqlite:database.db');
  $db->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );

/*
UPDATE products 
   SET price = 12 
 WHERE name = 'coke' AND price = 8;

*/


?>
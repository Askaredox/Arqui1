<?php
// set the default timezone to use. Available since PHP 5.1
date_default_timezone_set('America/Guatemala');


// Prints something like: Monday
//echo date("l");

// Prints something like: Monday 8th of August 2005 03:12:46 PM
$date = date('l jS \of F Y ');
echo ('"\n"');
$hour= date('h:i:s A');

echo($date.' hora: '.$hour);

?>
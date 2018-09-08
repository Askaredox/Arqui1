<?php

require '../vendor/autoload.php';
$db= (new MongoDB\Client('mongodb://127.0.0.1/'))->nueva;
$collectionB = $db->Correcta;


if($_GET)
{
	$nueva = $_REQUEST["contraseña"];
	$contraseña = $collectionB->findOne();

	$mod = array(
		"contraseña"=>$nueva
	);

	if($collectionB->updateOne($contraseña, 
	  array('$set'=>$mod))){

		echo "Actualizacion contraseña correcta";
	  }else{
		echo "Fallo en reestablecimiento de contraseña";
	  }

}


?>
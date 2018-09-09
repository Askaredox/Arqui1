<?php

use \Psr\Http\Message\ServerRequestInterface as Request;
use \Psr\Http\Message\ResponseInterface as Response;


require '../vendor/autoload.php';

$app = new \Slim\App;

$db= (new MongoDB\Client('mongodb://ruthlechuga:8564872@clusterproyecto-shard-00-00-sgrbk.gcp.mongodb.net:27017,clusterproyecto-shard-00-01-sgrbk.gcp.mongodb.net:27017,clusterproyecto-shard-00-02-sgrbk.gcp.mongodb.net:27017/dbAlarmas?replicaSet=ClusterProyecto-shard-0&authSource=admin'))->dbGarage;
$collection = $db->intento;
$collectionB =$db->cpassword;//coleccion donde esta almacenada la correcta
date_default_timezone_set('America/Guatemala');

$app->get('/Garage/{contrasena}', function (Request $request, Response $response, array $args) {

	$date= date('l jS \of F Y ');
	$time = date('h:i:s A');
	$contraseñaIngresada = $args['contrasena'];
	$correcta = $collectionB->findOne();

	//Aqui iria la comparacion pero aun no sé en donde está almacenada la contraseña correcta

	if($contraseñaIngresada==$correcta['password'])
	{
		echo "<Autorizacion>1</Autorizacion>";//Esto es lo que da como salida si es igual o  no

					$insert = array(
						"fecha"=>$date,
						"hora"=>$time,
					);
					
					
					if($collection->insertOne($insert)){//ingresamos a la collecion intentos solamente los correctos
					//echo "dato insertado";
					}else{
					//	echo "inserción fallida";//no es necesario solo para saber si esta ingreseando o no los datos a la base
					}



	}else
	{
		echo "<Autorizacion>0</Autorizacion>";//solo retorna 0 o 1 por ser xml

	}
	
   
});

$app->run();



?>
<?php
/*require '../vendor/autoload.php';
$db= (new MongoDB\Client('mongodb://127.0.0.1/'))->nueva;
$collection = $db->Contraseñas;
$collectionB = $db->Correcta;

date_default_timezone_set('America/Guatemala');
 if($_GET){

	
				$date= date('l jS \of F Y ');
				$time = date('h:i:s A');
				$contraseñaIngresada=$_REQUEST["contraseña"];
				$contraseñaCorrecta= $collectionB->findOne();
				
				if($contraseñaIngresada!=""){
				if($contraseñaIngresada==$contraseñaCorrecta['contraseña'])
				{
					
					echo "<Autorizacion>1</Autorizacion>";
					$insert = array(
						"fecha"=>$date,
						"hora"=>$time,
						"intento"=>"true"
					);
					
					
					
					
					if($collection->insertOne($insert)){
					echo "dato insertado";
					}else{
						echo "inserción fallida";
					}

				}else{
					echo "<Autorizacion>0</Autorizacion>";
				}
			}				

}


/**else if($_GET)
{
					

	//$contraseña=$_REQUEST["contraseña"];
	$intento=$_REQUEST["intento"];

	$buscar = array(
		"intento"=>$intento
	);
	
	$bus= $collection->findOne($buscar);

	 echo( "contraseña: ".$bus['contraseña']."  intento:".$bus['intento']."fecha: ".$bus['fecha']." hora:".$bus['hora'] );
}*/

use \Psr\Http\Message\ServerRequestInterface as Request;
use \Psr\Http\Message\ResponseInterface as Response;


require '../vendor/autoload.php';

$app = new \Slim\App;

date_default_timezone_set('America/Guatemala');

$app->get('/Garage/{contrasena}', function (Request $request, Response $response, array $args) {

	$date= date('l jS \of F Y ');
	$time = date('h:i:s A');
	$contraseñaIngresada = $args['contrasena'];
	echo $date
	echo $time
    echo $contraseñaIngresada;

   // return $response;
});

$app->run();



?>
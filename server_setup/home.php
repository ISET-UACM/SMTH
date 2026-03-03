<?php
// Anexo 17: Código PHP (home.php) para Recepción y Almacenamiento de Datos de Sensores

// Obtener los datos de la URL y sanitizarlos
for ($i = 1; $i <= 16; $i++) {
    ${"temperatura_S".$i} = isset($_GET['temp'.$i]) ? floatval($_GET['temp'.$i]) : 0;
    ${"humedad_S".$i} = isset($_GET['hum'.$i]) ? intval($_GET['hum'.$i]) : 0;
}

// Datos de conexion a la base de datos
$usuario = "root";
$contra = "password";
$servidor = "localhost";
$basededatos = "PROYECTO";

$conexion = mysqli_connect($servidor, $usuario, $contra, $basededatos);

if (!$conexion) {
    die("Conexion fallida: " . mysqli_connect_error());
}

// Inserción masiva
$consulta = "INSERT INTO datos (";
for ($i = 1; $i <= 16; $i++) {
    $consulta .= "fecha_S$i, temperatura_S$i, humedad_S$i" . ($i < 16 ? ", " : "");
}
$consulta .= ") VALUES (";
for ($i = 1; $i <= 16; $i++) {
    $tempVar = "temperatura_S$i";
    $humVar = "humedad_S$i";
    $consulta .= "'" . date("Y-m-d H:i:s") . "', '" . $$tempVar . "', '" . $$humVar . "'" . ($i < 16 ? ", " : "");
}
$consulta .= ")";

mysqli_query($conexion, $consulta);
mysqli_close($conexion);

// Guardar en archivo de texto para Nagios
$datosSensores = [];
for ($i = 1; $i <= 16; $i++) {
    $tempVar = "temperatura_S$i";
    $humVar = "humedad_S$i";
    $datosSensores[] = "$i, " . $$tempVar . ", " . $$humVar;
}
file_put_contents('/var/www/your_domain/sensores.txt', implode(PHP_EOL, $datosSensores) . PHP_EOL);
?>

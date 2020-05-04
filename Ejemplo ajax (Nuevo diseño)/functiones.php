<?php

try {
    $connection = new PDO("mysql:host=localhost;dbname=iehpuse_prueba", "root", "");
    echo json_encode("Exito al conectar a la base de datos");
} catch (PDOException $e) {
    echo json_encode("Error: $e.getMessage()");
}

?>
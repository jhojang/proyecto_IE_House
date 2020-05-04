<?php

try {
    $connection = new PDO("mysql:host=localhost;dbname=iehouse_prueba", "root", "");

    $statement = $connection->prepare("SELECT * FROM bombillo");
    $statement->execute();

    $resultado = $statement->fetchAll();

    if (!empty($resultado)) {
        echo json_encode($resultado);
    } else {
        echo json_encode("no se ha encontrado nada");
    }

    

} catch (PDOException $e) {
    echo json_encode("Error: $e.getMessage()");
}

?>
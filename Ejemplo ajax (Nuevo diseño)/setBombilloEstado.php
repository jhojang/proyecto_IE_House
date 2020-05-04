<?php
    $id_bombillo = (int)$_POST["id"];
    $estado = $_POST["state"];

    try {
        $connection = new PDO("mysql:host=localhost;dbname=iehouse_prueba", "root", "");
    
        $statement = $connection->prepare("UPDATE bombillo SET estado = :estado WHERE id_bombillo = :id_bombillo");
        $statement->execute([":estado" => $estado, ":id_bombillo" => $id_bombillo]);
        
        echo json_encode("Estado cambiado con exito");

    } catch (PDOException $e) {
        echo json_encode("Error: $e.getMessage()");
    }

?>
<?php

$nombre_cuarto = $_POST["room_item"];

if ($nombre_cuarto === "") {
    echo json_encode("Ingrese un room");
} else {
    try {
        $connection = new PDO("mysql:host=localhost;dbname=iehouse_prueba", "root", "");
    
        $statement = $connection->prepare("SELECT * FROM cuarto WHERE nombre_cuarto = :nombre_cuarto");
        $statement->execute([":nombre_cuarto" => $nombre_cuarto]);

        $resultado = $statement->fetch();

        if (!empty($resultado)) {
            echo json_encode("El cuarto ya existe");
        } else {
            $statement = $connection->prepare("INSERT INTO cuarto (nombre_cuarto) VALUES (:nombre_cuarto)");
            $statement->execute([":nombre_cuarto" => $nombre_cuarto]);

            echo json_encode("Exito al añadir el cuarto");
        }

    } catch (PDOException $e) {
        echo json_encode("Error: $e.getMessage()");
    }
}

?>


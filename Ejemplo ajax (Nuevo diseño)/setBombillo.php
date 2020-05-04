<?php

$nombre_bombillo = $_POST["nombre_bombillo"];
$cuarto_bombillo = (int) $_POST["cuarto_bombillo"];
$user = (int) $_POST["user"];


if ($nombre_bombillo === "" || $cuarto_bombillo === "" || $user === "") {
    echo json_encode("Seleccione todas las opciones");
}else {

    try {
        $connection = new PDO("mysql:host=localhost;dbname=iehouse_prueba", "root", "");
    
        $statement = $connection->prepare("SELECT * FROM bombillo WHERE nombre_bombillo = :nombre_bombillo");
        $statement->execute([":nombre_bombillo" => $nombre_bombillo]);

        $resultado = $statement->fetch();

        if (!empty($resultado)) {
            echo json_encode("El bombillo ya existe");
        } else {
            $statement = $connection->prepare("INSERT INTO bombillo (nombre_bombillo, estado, id_cuarto_fk) VALUES (:nombre_bombillo, :estado, :id_cuarto_kf)");
            $statement->execute([":nombre_bombillo" => $nombre_bombillo, ":estado" => false, ":id_cuarto_kf" => $cuarto_bombillo]);

            $statement = $connection->prepare("SELECT id_bombillo FROM bombillo WHERE nombre_bombillo = :nombre_bombillo");
            $statement->execute([":nombre_bombillo" => $nombre_bombillo]);

            $resultado = $statement->fetch();

            $statement = $connection->prepare("INSERT INTO user_bombillo (id_user_fk1, id_bombillo_fk1) VALUES (:id_user_fk1, :id_bombillo_fk1)");
            $statement->execute([":id_user_fk1" => $user, ":id_bombillo_fk1" => $resultado[0]]);

            echo json_encode($resultado[0]);
        }

    } catch (PDOException $e) {
        echo json_encode("Error: $e.getMessage()");
    }
}

?>
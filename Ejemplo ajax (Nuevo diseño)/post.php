<?php

$nombre = $_POST["nombre"];
$telefono = $_POST["telefono"];
$celular = $_POST["celular"];

if ($nombre === "" || $telefono === "" || $celular === "") {
    echo json_encode("Llena todos los campos");
} else {

    try {
        $connection = new PDO("mysql:host=localhost;dbname=directorio", "root", "");
        
        $statement = $connection->prepare("SELECT * FROM contactos WHERE nombre_contacto = :nombre");
        $statement->execute([":nombre" => $nombre]);

        $resultado = $statement->fetch();

        if (!empty($resultado)) {
            echo json_encode("El usuario ya existe en el directorio");
        } else {
            $statement = $connection->prepare("INSERT INTO contactos (nombre_contacto, telefono_contacto, celular_contacto) VALUES (:nombre, :telefono, :celular)");
            $statement->execute([
                ":nombre"=>$nombre,
                ":telefono"=>$telefono,
                ":celular"=>$celular                                    
            ]);

            echo json_encode("Usuario agregado correctamente");
        }

    } catch (PDOException $e) {
     echo json_encode("No se ha podido conectar a la base de datos: $e.getMessage()");
    }
}



?>
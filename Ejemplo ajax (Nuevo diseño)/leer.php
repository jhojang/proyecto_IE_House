<?php

try {
    $connection = new PDO("mysql:host=localhost;dbname=directorio", "root", "");

    $statement = $connection->prepare("SELECT * FROM contactos");
    $statement->execute();

    $resultados = $statement->fetchAll();

    if (!empty($resultados)) {
        $arrayResultados = [];
        foreach ($resultado as $clave) {
            $arrayResultados[] = ["nombre: " => $clave["nombre_contacto"], "telefono: " => $clave["telefono_contacto"], "celular" = $clave["celular_contacto"]];
        }
    } else {
        echo json_encode("Error al traer los datos");
    }

} catch (PDOException $e) {
    echo json_encode("Error: $e.getMessage()");
}

?>
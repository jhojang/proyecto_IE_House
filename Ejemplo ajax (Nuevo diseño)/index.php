<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://fonts.googleapis.com/css2?family=Ubuntu:wght@400;700&display=swap" rel="stylesheet">
    <link href="fontawesome-free-5.13.0-web/css/all.css" rel="stylesheet">
    <link href="css/style.css?v=<?php echo time(); ?>" rel="stylesheet" type="text/css">
    <title>Document</title>
</head>
<body>
    <div class="contenedor">
        <header class="header">
                <nav>
                    <ul>
                        <li><a href="">Home</a></li>
                        <li><a href="">Horarios</a></li>
                        <li><a href="">Sobre Nosotros</a></li>
                        <li><a href="">Contacto</a></li>
                    </ul>
                </nav>
            
        </header>
        <main class="principal">
            
            <div class="content_left">
                <div class="titulo">
                    <h2>Buenos días Usuario!</h2>
                    <h1>Gestión de luces</h1>
                </div>
                <div class="bombillos_content">
                    <div class="rooms">
                        <ul>
                            <li><a href="" class="active link_cuarto">Todos</a></li>
                        </ul>
                        <form id="form_rooms" class="form_rooms_visible">
                            <input type="text" id="room_item" name="room_item" placeholder="Agregar room">
                            <input type="submit" value="Agregar">
                        </form>
                        <a href="" class="agregar_cuarto">+</a>
                    </div>
                    <div class="bombillos">
                    <button class="botonBombillo agregar_bombillo">+</button>
                    </div>
                    
                </div>
               
                <div class="modal modal_cerrar">
                    <a href="" class="boton_cerrar_modal">X</a>
                    <div class="nuevo_bombillo">
                        <img src="image/b9ead3f99800213fe312f5a82a4be058.png" alt="">
                        <form id="formAddBombillo">
                            <input type="text" id="nombre_bombillo" name="nombre_bombillo" placeholder="Nombre del bombillo">
                            <select name="cuarto_bombillo" id="cuarto_bombillo">

                            </select>
                            <div class="listado_usuarios">
                                
                            </div>
                            <input type="submit" value="Agregar">
                        </form>
                    </div>
                </div>
            </div>
            <div class="content_right"></div>
        </main>
        <aside class="sidebar">
            <div class="aside_content">
                <div class="hud">
                    <img src="image/LOGO.png" class="logo" alt="">
                    <img src="image/Eve.jpg" alt="" class="user_img">
                    <h2>Nombre usaurio</h2>
                    <div class="hr"></div>
                </div>
                <div class="menu_aside">
                    <ul class="lista_menu">
                        <li><a href="" class="active"> <i class="far fa-lightbulb"></i> Gestión de luces</a></li>
                        <li><a href=""><i class="fas fa-bolt"></i> Informe de energía</a></li>
                        <li><a href=""><i class="fas fa-user"></i> Control parental</a></li>
                        <li><a href=""><i class="fas fa-cog"></i> Configuración</a></li>
                    </ul>
                </div>
            </div>

        </aside>
    </div>
    <script src="main.js?v=<?php echo(rand()); ?>" type="text/javascript"></script>
</body>
</html>
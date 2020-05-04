"use strict"
var agregar_cuarto = document.querySelector(".agregar_cuarto");
var form_rooms = document.querySelector("#form_rooms");
var room_item = document.querySelector("#room_item");
var bombillos_content = document.querySelector(".bombillos_content");



cargarCuartos();
cargarBombillos();



//BOTÓN REDONDO PEQUEÑO (AGREGA CUARTOS)
agregar_cuarto.addEventListener("click", function(e){
    e.preventDefault();
    form_rooms.classList.toggle("form_rooms_visible");
    room_item.focus();
    agregar_cuarto.style.display = "none";
});

form_rooms.addEventListener("submit", function(e){
    e.preventDefault();
        
    var datos = new FormData(form_rooms);

    fetch("addCuarto.php", {
        method: "POST",
        body: datos
    })
    .then(res => res.json())
    .then(data => {
        console.log(data);
        cargarCuartos()
    });

    form_rooms.classList.toggle("form_rooms_visible");
    agregar_cuarto.style.display = "block";

});



//BOTÓN AZUL REDONO CON EL + (ABRE EL MODAL)
var modal = document.querySelector(".modal");
var agregar_bombillo = document.querySelector(".agregar_bombillo");

agregar_bombillo.addEventListener("click", function(){
    //modal.classList.toggle("modal_cerrar");
    modal.style.transform = "translateX(0%)"
    document.querySelector(".nuevo_bombillo").style.display = "block";




//OBTENER CUARTOS
    fetch("getCuarto.php", {
        method: "GET"
    })
    .then(res => res.json())
    .then(data => {
        var cuarto_bombillo = document.querySelector("#cuarto_bombillo");
        let elementosHijos = document.querySelectorAll("#cuarto_bombillo > option");
        
        borrarHijos(elementosHijos, cuarto_bombillo)
        for (let i in data) {
            let option = document.createElement("option");
            option.setAttribute("value", data[i].id_cuarto);
            option.innerHTML = data[i].nombre_cuarto;
            cuarto_bombillo.appendChild(option);
        }
        return fetch("getUsuarios.php", {method: "GET"})
    })
    .then(res => res.json())
    .then(data => {
        var listado_usuarios = document.querySelector(".listado_usuarios");
        let elementosHijos = document.querySelectorAll(".listado_usuarios > p");

        borrarHijos(elementosHijos, listado_usuarios)
        for (let i in data) {
            let input = document.createElement("input");
            let label = document.createElement("label");
            let p = document.createElement("p");
            input.setAttribute("name", "user");
            input.setAttribute("id", "user" + data[i].id_user);
            input.setAttribute("value", data[i].id_user);
            input.setAttribute("type", "checkbox");
            label.setAttribute("for", "user" + data[i].id_user);
            label.innerHTML = data[i].nombre_user;
            p.appendChild(input);
            p.appendChild(label);
            listado_usuarios.appendChild(p);
            
        }
    });
});


//BOTÓN CERRAR MODAL
var cerrar_modal = document.querySelector(".boton_cerrar_modal");
cerrar_modal.addEventListener("click", function(e){
    e.preventDefault();
    modal.style.transform = "translateX(150%)"
    document.querySelector(".nuevo_bombillo").style.display = "none";
});


//AGREGAR BOMBILLOS
var formAddBombillo = document.querySelector("#formAddBombillo");
formAddBombillo.addEventListener("submit", function(e){
    e.preventDefault();

    var datos = new FormData(this);

    fetch("setBombillo.php", {
        method: "POST",
        body: datos
    })
    .then(res => res.json())
    .then(data => {
        alert(data);

        cargarBombillos();
    });

    this.reset();

});



//SE ACTUALIZAN LOS BOMBILLOS

function cargarBombillos() {
     fetch("getBombillo.php", {method: "GET" })
   
    .then(res => res.json())
    .then(data => {
        var bombillos = document.querySelector(".bombillos");
        var botonBombillo = document.querySelectorAll(".bombillos > .botonBombillo");
        
        for (let k = 0; k < botonBombillo.length-1; k++) {
            bombillos.removeChild(botonBombillo[k]);
        }

        for (let i in data) {
            let button = document.createElement("button");
            button.setAttribute("id", data[i].id_bombillo);
            button.className = "botonBombillo";
            
            if (data[i].estado == 0) {
                button.classList.remove("botonBombilloActivo");
            } else {
                button.classList.add("botonBombilloActivo");
            }
            let template = `<span>${data[i].nombre_bombillo}</span><div><i class="far fa-lightbulb"></i></div>`;
            button.innerHTML = template;
            bombillos.prepend(button);
            
        }


        var botonBombillo = document.querySelectorAll(".bombillos > .botonBombillo");
        for (let i = 0; i < botonBombillo.length-1; i++) {
            botonBombillo[i].addEventListener("click", function(){
                this.classList.toggle("botonBombilloActivo");
                var estado = this.getAttribute("class").indexOf("botonBombilloActivo");
                if (estado > -1) {
                    estado = 1;
                } else {
                    estado = 0;
                }

                var datos = {
                    id: botonBombillo[i].getAttribute("id"),
                    state: estado 
                }
                
                var data = new FormData();

                for (let i in datos ) {
                    data.append(i, datos[i]);
                }

                fetch("setBombilloEstado.php", {
                    method: "POST",
                    body: data
                })
                .then(res => res.json())
                .then(data => {
                    console.log(data);
                });
            }) 
        }

        
    });
}




/*SE ACTUALIZAN LOS CUARTOS*/
function cargarCuartos(){
    fetch("getCuarto.php", {
        method: "GET"
    })
    .then(res => res.json())
    .then(data => {
        
        var ul = document.querySelector(".bombillos_content .rooms ul");
        let elementosHijos = document.querySelectorAll(".rooms > ul > li");

        if (elementosHijos.length > 1) {
            for (let k = 1; k < elementosHijos.length; k++) {
                ul.removeChild(elementosHijos[k]);
            }
        }
        
        for (let i in data) {
            let li = document.createElement("li");
            let plantilla = `<a href="" class="link_cuarto">${data[i].nombre_cuarto}</a>`;
            li.innerHTML = plantilla;
            ul.appendChild(li);
        }
    
        var array_room_item = document.querySelectorAll(".link_cuarto");
        for (let i = 0; i < array_room_item.length; i++) {
            array_room_item[i].addEventListener("click", function(e){
                e.preventDefault();
                this.className = "active";
                for (let j = 0; j < array_room_item.length; j++) {
                    if (this == array_room_item[j]) {
                        continue;
                    } else {
                        array_room_item[j].classList.remove("active");
                    }
                }
            });
        }
    });
}

function borrarHijos(elementosHijos, elementoPadre){
    for (let k = 0; k < elementosHijos.length; k++) {
        elementoPadre.removeChild(elementosHijos[k]);
    }
}




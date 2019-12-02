//Registro e inicio de sesión usuarios

function arrayJSON(user,name,email,lastName,pass,passConfirm){
    var data = {
        user : user,
        email : email,
        name : name,
        lastName : lastName,
        pass : pass,
        passConfirm : passConfirm
    };
    return data;
}

function getDatos()
{
    var user = document.getElementById('user').value;
    var email = document.getElementById('email').value;
    var name = document.getElementById('name').value;
    var lastName = document.getElementById('lastName').value;
    var pass = document.getElementById('pass').value;
    var passConfirm = document.getElementById('passConfirm').value;

    if(user.length==0 || email.length==0 || name.length==0 || lastName.length==0 || pass==0 || passConfirm==0){
        alert("Debes llenar todos los campos");
    } else if(pass != passConfirm){
        alert("Las contraseñas no coinsiden");
    } else {
        var arrayData = arrayJSON(user,email,name,lastName,pass,passConfirm);
        console.log(arrayData);
        firebase.auth().createUserWithEmailAndPassword(email, pass).catch(function(error) {
            // Handle Errors here.
            var errorCode = error.code;
            var errorMessage = error.message;
            alert(errorCode +  "\n" + errorMessage);
          });
    }
}


//Ingreso de usuarios
function ingresar(){
    var email = document.getElementById('email').value;
    var password = document.getElementById('password').value;
    console.log(email+" "+password);

    firebase.auth().signInWithEmailAndPassword(email, password)
    .then(function(result) {
        // Handle Errors here.
        window.location.href = "C:/Users/Jhojan/Desktop/proyectoIeHouse/proyecto_IE_House/prototipoWeb/html/principal.html";
        // ...
      })
    
    .catch(function(error) {
        // Handle Errors here.
        var errorCode = error.code;
        var errorMessage = error.message;
        // ...
        alert("Email o contraseña incorrectos");
      });
}


//Cambio de brillo de los botones
var btnR = document.getElementById('bombiRojo');
var cambioR = true;
function cambioColorRojo()
{
    if(cambioR == true)
    {
        btnR.classList.remove('a-btnRA');
        btnR.classList.add('a-btnRE');
        cambioR = false;
    } else {
        btnR.classList.remove('a-btnRE');
        btnR.classList.add('a-btnRA');
        cambioR = true;
    }
            
}

var btnB = document.getElementById("bombiBlue");
var cambioB = true;
function cambioColorBlue()
{
    if(cambioB == true)
    {
        btnB.classList.remove('a-btnBA');
        btnB.classList.add('a-btnBE')
        cambioB = false;
    } else {
        btnB.classList.remove('a-btnBE');
        btnB.classList.add('a-btnBA');
        cambioB = true;
    }
}

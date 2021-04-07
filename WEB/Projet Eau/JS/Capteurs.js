function getTemperature() {
    //pour appeler une API on utilise la méthode fetch()
    fetch('API/temperature.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdateDivTemp("Temp", data);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            //console.log(error);
        });
}

function getNiv1() {
    //pour appeler une API on utilise la méthode fetch()
    fetch('API/niveau1.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdateDivNiv1("Niv1", data);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            //console.log(error);
        });
}
//Va permettre le refresh auto de la temperature (id de la div, text = les données retourné)
function UpdateDivTemp(id, text) {
    var e = document.getElementById(id).innerHTML = "La temperature est de " + text + "° C";
    //Si on ne peut pas afficher
    if (text == false) {
        var e = document.getElementById(id).innerHTML = "Le serveur TCP n'est pas actif";
    }
}
//Va permettre le refresh auto du niveau bas de la cuve (id de la div, text = les données retourné)
function UpdateDivNiv1(id, text) {
    //Si on ne peut pas afficher
    if (text == false) {
        var e = document.getElementById(id).innerHTML = "Le serveur TCP n'est pas actif";
    } else if (text == "haut") {
        var e = document.getElementById(id).innerHTML = "L'eau de pluie est au niveau bas";
    } else if (text == "bas") {
        var e = document.getElementById(id).innerHTML = "L'eau de pluie est au niveau haut";
    }
}
//Va permettre le refresh auto du niveau haut de la cuve (id de la div, text = les données retourné)
function UpdateDivNiv2(id, text) {
    //Si on ne peut pas afficher
    if (text == false) {
        var e = document.getElementById(id).innerHTML = "Le serveur TCP n'est pas actif";
    } else if (text == "bas") {
        var e = document.getElementById(id).innerHTML = "La cuve a besoin d'être remplie";
    } else if (text == "haut") {
        var e = document.getElementById(id).innerHTML = "La cuve peut être utilisé";
    }
}
//Va permettre le refresh auto du niveau de la cuve de pluie (id de la div, text = les données retourné)
function UpdateDivNiv3(id, text) {
    var e = document.getElementById(id).innerHTML = "Le niveau d'eau 3 est à l'état " + text;
    //Si on ne peut pas afficher
    if (text == false) {
        var e = document.getElementById(id).innerHTML = "Le serveur TCP n'est pas actif";
    } else if (text == "bas") {
        var e = document.getElementById(id).innerHTML = "La cuve peut etre encore remplie";
    } else if (text == "haut") {
        var e = document.getElementById(id).innerHTML = "La cuve est remplie (ne pas pomper)";
    }
}

function getNiv2() {
    //pour appeler une API on utilise la méthode fetch()
    fetch('API/niveau2.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdateDivNiv2("Niv2", data);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            //console.log(error);
        });
}


function getNiv3() {
    //pour appeler une API on utilise la méthode fetch()
    fetch('API/niveau3.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdateDivNiv3("Niv3", data);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            //console.log(error);
        });
}

function StopServer() {
    //pour appeler une API on utilise la méthode fetch()
    fetch('API/Deconnxion.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdateDivDegre("infoTemp", data);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            //console.log(error);
        });


}

function addConsoValue() {
    console.log(chart.data.datasets);
    this.chart.data.datasets[0].data.push(7, 8);
}

refreshValuesTime = 2000;
//On refresh les valeurs des capteurs
setInterval("getNiv3()", refreshValuesTime);
setInterval("getTemperature()", refreshValuesTime);
setInterval("getNiv1()", refreshValuesTime);
setInterval("getNiv2()", refreshValuesTime);

//setInterval("addConsoValue()", 5000);
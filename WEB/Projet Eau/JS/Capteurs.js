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
//Va permettre le refresh auto de la temperature (id de la div, text = les données retourné)
function UpdateDivTemp(id, text) {
    var e = document.getElementById(id).innerHTML = "La temperature est de " + text + "° C";
    //Si on ne peut pas afficher
    if (text == "") {
        var e = document.getElementById(id).innerHTML = "Le serveur TCP n'est pas actif";
    }
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
//Va permettre le refresh auto du niveau bas de la cuve (id de la div, text = les données retourné)
function UpdateDivNiv1(id, text) {
    
    //Si on ne peut pas afficher
    if (text == "") {
        var e = document.getElementById(id).innerHTML = "Le serveur TCP n'est pas actif";
    } else if (text == '0') {
        var e = document.getElementById(id).innerHTML = "La cuve d'alimentation est a l'état bas";
    }
    else if (text == '1') {
        var e = document.getElementById(id).innerHTML = "La cuve d'alimentation est remplie";
    }
}
//Va permettre le refresh auto du niveau haut de la cuve (id de la div, text = les données retourné)
function UpdateDivNiv2(id, text) {
    var e = document.getElementById(id).innerHTML = "Le niveau d'eau 2 est à l'état " + text;
    //Si on ne peut pas afficher
    if (text == "") {
        var e = document.getElementById(id).innerHTML = "Le serveur TCP n'est pas actif";
    } else if (text == "0") {
        var e = document.getElementById(id).innerHTML = "Le niveau bas de la cuve n'est pas actif";
    } else if (text == "1") {
        var e = document.getElementById(id).innerHTML = "Le niveau bas de la cuve est actif";
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
//Va permettre le refresh auto du niveau de la cuve de pluie (id de la div, text = les données retourné)
function UpdateDivNiv3(id, text) {
    var e = document.getElementById(id).innerHTML = "Le niveau d'eau 3 est à l'état " + text;
    //Si on ne peut pas afficher
    if (text == "") {
        var e = document.getElementById(id).innerHTML = "Le serveur TCP n'est pas actif";
    } else if (text == "0") {
        var e = document.getElementById(id).innerHTML = "La cuve peut etre encore remplie";
    } else if (text == "1") {
        var e = document.getElementById(id).innerHTML = "La cuve est remplie (ne pas pomper)";
    }
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
function getPumpStatus() {
    //pour appeler une API on utilise la méthode fetch()
    //pour appeler une API on utilise la méthode fetch()
    fetch('API/Pompe.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdatePumpStatus("Pompe", data);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            //console.log(error);
        });
}


//Va permettre le refresh auto du niveau de la cuve de pluie (id de la div, text = les données retourné)
function UpdatePumpStatus(id, text) {
    //Si on ne peut pas afficher
    if (text == "") {
        var e = document.getElementById(id).innerHTML = "Le serveur TCP n'est pas actif";
    } else if (text == "0") {
        var e = document.getElementById(id).innerHTML = "La pompe est eteinte";
    } else if (text == "1") {
        var e = document.getElementById(id).innerHTML = "La pompe est entrain d'être utilisé";
    }
}

function getWaterflowStatus() {
    //pour appeler une API on utilise la méthode fetch()
    //pour appeler une API on utilise la méthode fetch()
    fetch('API/WaterFlow.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdateWaterFlowStatus("WaterFlow", data);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            //console.log(error);
        });
}
 
//Va permettre le refresh auto du niveau de la cuve de pluie (id de la div, text = les données retourné)
function UpdateWaterFlowStatus(id, text) {
    //Si on ne peut pas afficher

    //Si on ne peut pas afficher
    if (text == "") {
        var e = document.getElementById(id).innerHTML = "Le serveur TCP n'est pas actif";
    } else if (text == "1") {
        var e = document.getElementById(id).innerHTML = "L'eau de pluie est utilisée";
    } else if (text == "0") {
        var e = document.getElementById(id).innerHTML = "L'eau courante est utilisée";
    }
}

function UpdateInsertBddStatus(id, text) {
    if (text == true)
    {
        var e = document.getElementById(id).innerHTML = "Insert into consommation OK";
    }
    else
    {
        var e = document.getElementById(id).innerHTML = "Pas réussi à insert dans consommation";
    }
}
function addConsoValue() {
    console.log(chart.data.datasets);
    this.chart.data.datasets[0].data.push(7, 8);
}

refreshValuesTime = 4800;
//On refresh les valeurs des capteurs
setInterval("getTemperature()", refreshValuesTime);
setInterval("getNiv1()", refreshValuesTime);
setInterval("getNiv2()", refreshValuesTime);
setInterval("getNiv3()", refreshValuesTime);
setInterval("getPumpStatus()", refreshValuesTime);
setInterval("getWaterflowStatus()", refreshValuesTime);
// Pause de 10 minutes pour l'insert en base.
//setInterval("addConsoValue()", 5000)
<script src="../Projet Eau/JS/Capteurs.js"></script>
<h3>Temperature</h3>
<p id="temperature"> 
</p>

<h3>Niveau 1</h3>
<p id="niveau1"> </p>


<h3>Niveau 2</h3>
<p id="niveau2"> </p>

<h3>Niveau 3</h3>
<p id="niveau3"> </p>

<h3>Pompe</h3>
<p id="Pump"> </p>

<h3>Réseau Eau</h3>
<p id="Electrovanne"></p>

<script>
function getTemperature() {
    //pour appeler une API on utilise la méthode fetch()
    fetch('../Projet Eau/API/temperature.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdateDivTemp("temperature", data);
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
    fetch('../Projet Eau/API/niveau1.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdateDivNiv1("niveau1", data);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            //console.log(error);
        });
}
//Va permettre le refresh auto du niveau bas de la cuve (id de la div, text = les données retourné)
function UpdateDivNiv1(id, text) {
    var e = document.getElementById(id).innerHTML = "Le niveau d'eau 1 est à l'état " + text;
    //Si on ne peut pas afficher
    if (text == "") {
        var e = document.getElementById(id).innerHTML = "Le serveur TCP n'est pas actif";
    } else if (text == '0') {
        var e = document.getElementById(id).innerHTML = "La cuve est a l'état bas";
    }
}
//Va permettre le refresh auto du niveau haut de la cuve (id de la div, text = les données retourné)
function UpdateDivNiv2(id, text) {
    var e = document.getElementById(id).innerHTML = "Le niveau d'eau 2 est à l'état " + text;
    //Si on ne peut pas afficher
    if (text == "") {
        var e = document.getElementById(id).innerHTML = "Le serveur TCP n'est pas actif";
    } else if (text == "0") {
        var e = document.getElementById(id).innerHTML = "La cuve est a l'état bas";
    } else if (text == "1") {
        var e = document.getElementById(id).innerHTML = "La cuve est remplie (ne pas pomper)";
    }
}



function getNiv2() {
    //pour appeler une API on utilise la méthode fetch()
    fetch('../Projet Eau/API/niveau2.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdateDivNiv2("niveau2", data);
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
    fetch('../Projet Eau/API/niveau3.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdateDivNiv3("niveau3", data);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            //console.log(error);
        });
}

function StopServer() {
    //pour appeler une API on utilise la méthode fetch()
    fetch('../Projet Eau/API/Deconnxion.php').then((response) => response.json())
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
    fetch('../Projet Eau/API/Pompe.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdatePumpStatus("Pump", data);
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

function getWaterFlowStatus() {
    //pour appeler une API on utilise la méthode fetch()
    fetch('../Projet Eau/API/WaterFlow.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log(data);
            UpdateWaterFlowStatus("Electrovanne", data);
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
    } else if (text == "0") {
        var e = document.getElementById(id).innerHTML = "La cuve peut etre encore remplie";
    } else if (text == "1") {
        var e = document.getElementById(id).innerHTML = "La cuve est remplie (ne pas pomper)";
    }
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
setInterval("getPumpStatus()", refreshValuesTime);
setInterval("getWaterFlowStatus()", refreshValuesTime);

//setInterval("addConsoValue()", 5000)

</script>
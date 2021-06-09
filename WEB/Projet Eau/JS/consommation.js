function updateChart() {
    //pour appeler une API on utilise la méthode fetch()
    fetch('API/Conso.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            console.log("temperature : " + data);
            //console.log("Heure : " + data[1]);
            //addData(chart, 15, data);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            console.log(error);
        });
}

function updateDivCourante(id, text)
{
    document.getElementById(id).innerHTML = text;
}

function updateDivPluie(id, text)
{
    document.getElementById(id).innerHTML = text;
}

function updateDivElec(id, text)
{
    document.getElementById(id).innerHTML = text;
}

function getAllConsommations() {
    //pour appeler une API on utilise la méthode fetch()
    fetch('API/displayConsommation.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            //updateDivCourante("courante", 14, 12);
            //updateDivPluie("pluie", 8);
            //updateDivElec("elec", 6);
            console.log("eau Courante : " + data.eauCourante);
            console.log("eau pluie : " + data.eauPluie);
            console.log("electrique : " + data.electrique);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            console.log(error);
        });
}

function displayJour(id, text) {
    document.getElementById(id).innerHTML = text;
}

function getOnlyOneDate()
{
    fetch('API/displayConsoByDate.php').then((response) => response.json())
        .then(function(data) {
            // data est la réponse http de notre API.
            displayJour("jour", data);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            console.log(error);
        });
}

//setInterval("updateChart()", 10000);
//setInterval("info()", 10000);
//setInterval("getAllConsommations()", 1000);
//setInterval("getOnlyOneDate()", 1000);

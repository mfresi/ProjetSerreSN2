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

function addData(chart, label, data) {
    chart.data.labels.push(label);
    chart.data.datasets.forEach((dataset) => {
        dataset.data.push(data);
    });
    chart.update();
}

function info()
{
    // Parametre -> chart, heure, valueConso
    addData(chart, 10, 19);
    console.log("Div Maj");
}

//setInterval("updateChart()", 10000);
//setInterval("info()", 10000);

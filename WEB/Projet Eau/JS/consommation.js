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



//setInterval("updateChart()", 10000);
//setInterval("info()", 10000);

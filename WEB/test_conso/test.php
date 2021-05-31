<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>test update conso</title>
    <script src="conso.js"></script>

    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
</head>
<script>
    function setInterval() {
        var minGraphValue = document.getElementById("minGraph").value;
        var maxGraphValue = document.getElementById("maxGraph").value;
        var minConvert = parseInt(minGraphValue);
        var maxConvert = parseInt(maxGraphValue);
        chart.options.scales.x.min = minConvert;
        chart.options.scales.x.max = maxConvert;
        chart.update();
        console.log("chart mis à jour");
    }

    function addData(chart, label, data) {
    chart.data.labels.push(label);
    chart.data.datasets.forEach((dataset) => {
        dataset.data.push(data);
        console.log(data);
    });
    chart.update();
    console.log("chart update");
}
</script>

<body>
    <div id="Graphique"><canvas height="70" id="myChart"></canvas></div>

    <select id="minGraph" name="Heure min">
        <option>Heure Min</option>
        <option value="1">1</option>
        <option value="2">2</option>
        <option value="3">3</option>
        <option value="4">4</option>
        <option value="5">5</option>
        <option value="6">6</option>
        <option value="7">7</option>
        <option value="8">8</option>
        <option value="9">9</option>
        <option value="10">10</option>
        <option value="11">11</option>
        <option value="12">12</option>
        <option value="13">13</option>
        <option value="14">14</option>
        <option value="15">15</option>
    </select>

    <select id="maxGraph" name="Heure max">
        <option>Heure Max</option>
        <option value="1">1</option>
        <option value="2">2</option>
        <option value="3">3</option>
        <option value="4">4</option>
        <option value="5">5</option>
        <option value="6">6</option>
        <option value="7">7</option>
        <option value="8">8</option>
        <option value="9">9</option>
        <option value="10">10</option>
        <option value="11">11</option>
        <option value="12">12</option>
        <option value="13">13</option>
        <option value="14">14</option>
        <option value="15">15</option>
    </select>

    <button onclick="setInterval()">Filtrer la date</button>

</body>

</html>

<script>
    var ctx = document.getElementById('myChart');
    var chart = new Chart(ctx, {
        // Le type de graphique
        type: 'line',
        // Les données
        data: {
            labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
            datasets: [{
                    label: 'Consommation en eau courante en fonction du temps',
                    backgroundColor: 'rgb(51, 209, 255)',
                    borderColor: 'rgb(51, 209, 255)',
                    data: [10, 9, 7, 20, 1, 4, 15, 18, 5, 6, 12, 3]
                },
                {
                    label: 'Consommation en eau de pluie en fonction du temps',
                    backgroundColor: 'rgb(51, 255, 249)',
                    borderColor: 'rgb(51, 255, 249)',
                    data: [18, 7, 6, 10, 19, 15, 3, 5, 11, 14, 17]
                }
            ]
        },
        // Configuration options go here
        options: {
            scales: {
                x: {
                    min: 0,
                    max: 15
                }
            }
        }
    });

    setInterval("addData()", 10000);
</script>
function insertBDD() 
{
    //pour appeler une API on utilise la méthode fetch()
    fetch('API/Conso.php').then((response) => response.json())
        .then(function(data) 
        {
            // data est la réponse http de notre API.
            console.log(data);
            UpdateDivConso("conso", data);
        })
        .catch(function(error) {
            // This is where you run code if the server returns any errors
            //console.log(error);
        });
}

function UpdateDivConso(id, text) 
{
    if (text == true) {
        var e = document.getElementById(id).innerHTML = "Connexion à la base OK";
    }
    else
    {
        var e = document.getElementById(id).innerHTML = "Pas réussi à connecter en base";
    }
}

setInterval("insertBDD()", 60000);
 //setInterval("refreshWaterConso()", 1000);


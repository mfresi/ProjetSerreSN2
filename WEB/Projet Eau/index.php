<?php include("class/capteurs.php"); ?>

<head>
    <meta charset="utf-8">
    <title>LaProSerre</title>
    <meta name="description" content="">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" type="image/png" href="favicon.ico">


    <!--Google Font link-->
    <link href="https://fonts.googleapis.com/css?family=Ubuntu:300,300i,400,400i,500,500i,700,700i" rel="stylesheet">

    <link rel="stylesheet" href="assets/css/swiper.min.css">
    <link rel="stylesheet" href="assets/css/animate.css">
    <link rel="stylesheet" href="assets/css/iconfont.css">
    <link rel="stylesheet" href="assets/css/font-awesome.min.css">
    <link rel="stylesheet" href="assets/css/bootstrap.min.css">
    <link rel="stylesheet" href="assets/css/magnific-popup.css">
    <link rel="stylesheet" href="assets/css/bootsnav.css">
    <link href="http://fonts.googleapis.com/css?family=Roboto:300,400,700|" rel="stylesheet" type="text/css">
    <!--For Plugins external css-->
    <!--<link rel="stylesheet" href="assets/css/plugins.css" />-->
    <!--Theme custom css -->
    <link rel="stylesheet" href="assets/css/style.css">

    <!--Theme Responsive css-->
    <link rel="stylesheet" href="assets/css/responsive.css" />

    <script src="assets/js/vendor/modernizr-2.8.3-respond-1.4.2.min.js"></script>
</head>

<script>
    function displayJour(id, text) {
        document.getElementById(id).innerHTML = text;
    }

    function setIntervalGraph() {
        var minGraphValue = document.getElementById("minGraph").value;
        var maxGraphValue = document.getElementById("maxGraph").value;
        var date = document.getElementById("dateSelected").value;
        var minConvert = parseInt(minGraphValue);
        var maxConvert = parseInt(maxGraphValue);
        displayJour("jour", date);
        chart.options.scales.x.min = minConvert;
        chart.options.scales.x.max = maxConvert;
        chart.update();
        console.log("chart mis à jour");
    }
</script>

<?php
$conso = new capteurs;
?>

<body data-spy="scroll" data-target=".navbar-collapse">


    <!-- Preloader -->
    <div id="loading">
        <div id="loading-center">
            <div id="loading-center-absolute">
                <div class="object" id="object_one"></div>
                <div class="object" id="object_two"></div>
                <div class="object" id="object_three"></div>
                <div class="object" id="object_four"></div>
            </div>
        </div>
    </div>
    <!--End off Preloader -->


    <div class="culmn">
        <!--Home page style-->


        <nav class="navbar navbar-default bootsnav navbar-fixed white no-background">
            <div class="container">

                <!-- Start Atribute Navigation -->
                <div class="attr-nav">
                    <ul>

                    </ul>
                </div>
                <!-- End Atribute Navigation -->


                <!-- Start Header Navigation -->
                <div class="navbar-header">
                    <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#navbar-menu">
                        <i class="fa fa-bars"></i>
                    </button>
                    <a class="navbar-brand" href="#brand">
                        LA PRO SERRE
                    </a>
                </div>
                <!-- End Header Navigation -->

                <!-- navbar menu -->
                <div class="collapse navbar-collapse" id="navbar-menu">
                    <ul class="nav navbar-nav navbar-center">
                        <li><a href="#home">Accueil</a></li>
                        <li><a href="#Graphique">Graphiques</a></li>
                        <li><a href="page.php">Archives</a></li>
                    </ul>
                </div><!-- /.navbar-collapse -->
            </div>
        </nav>

        <!--Home Sections-->

        <section id="home" class="home">
            <div class="container">
                <div class="row">
                    <div class="main_home">
                        <div class="col-md-6">
                            <div class="home_text">
                                <h1 class="text-white">La Pro Serre</h1>
                            </div>

                            <div class="home_btns m-top-40">

                            </div>
                        </div>

                        <div class="col-md-6">
                            <div class="phone_one phone_attr1 text-center sm-m-top-50">
                                <h1 class="text-white">Prévision météo : </h1>
                                <iframe id="widget_autocomplete_preview" width="150" height="300" frameborder="0" src="https://meteofrance.com/widget/prevision/800210"> </iframe>
                            </div>
                        </div>

                    </div>
                </div>
                <!--End off row-->
            </div>
            <!--End off container -->
        </section>
        <!--End off Home Sections-->



        <!--Featured Section-->
        <section id="features" class="features">
            <div class="container">
                <div class="row">
                    <div class="main_features p-top-100">
                        <div class="col-md-4">
                            <div class="features_item sm-m-top-30">
                                <div class="f_item_icon">
                                    <img src="assets/icone-dicone-de-temperature-du-thermostat.png">
                                </div>
                                <div class="f_item_text">
                                    <h3>Temperature</h3>
                                    <p id="Temp"> </p>
                                </div>
                            </div>
                        </div>
                        <div class="col-md-4">
                            <div class="features_item sm-m-top-30">
                                <div class="f_item_icon">
                                    <img src="assets/robinet.png">
                                </div>
                                <div class="f_item_text">
                                    <h3>Niveau 1</h3>
                                    <p id="Niv1"> </p>
                                </div>
                            </div>
                        </div>
                        <div class="col-md-4">
                            <div class="features_item sm-m-top-30">
                                <div class="f_item_icon">
                                    <img src="assets/robinet.png">
                                </div>
                                <div class="f_item_text">
                                    <h3>Niveau 2</h3>
                                    <p id="Niv2"> </p>
                                </div>
                            </div>
                        </div>
                        <div class="col-md-4">
                            <div class="features_item sm-m-top-30">
                                <div class="f_item_icon">
                                    <img src="assets/robinet.png">
                                </div>
                                <div class="f_item_text">
                                    <h3>Niveau 3</h3>
                                    <p id="Niv3"> </p>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div class="col-md-4">
                        <div class="features_item sm-m-top-30">
                            <div class="f_item_icon">
                                <img src="assets/pompe.png">
                            </div>
                            <div class="f_item_text">
                                <h3>Pompe</h3>
                                <p id="Pompe"> </p>
                            </div>
                        </div>
                    </div>
                    <div class="col-md-4">
                        <div class="features_item sm-m-top-30">
                            <div class="f_item_icon">
                                <img src="assets/robinet.png">
                            </div>
                            <div class="f_item_text">
                                <h3>Réseau Eau</h3>
                                <p id="WaterFlow"> </p>
                            </div>
                        </div>
                    </div>
                </div><!-- End off row -->
            </div><!-- End off container -->
        </section><!-- End off Featured Section-->

        <section>
            <div class="container">
                <div class="row">
                    <div class="main_drag roomy-50">
                        <div class="col-md-12">
                            <div class="swiper-container">
                                <div class="swiper-wrapper">
                                    <div class="swiper-slide" style="background-color:white; color:rgb(0, 0, 0)" ;>
                                        <img src="assets/Serre4.jpg">
                                    </div>
                                    <div class="swiper-slide" style="background-color:white; color:rgb(0, 0, 0)" ;>
                                        <img src="assets/Serre1.jpg">
                                    </div>
                                    <div class="swiper-slide" style="background-color:white; color:rgb(0, 0, 0)" ;>
                                        <img src="assets/Serre2.jpg">
                                    </div>
                                    <div class="swiper-slide" style="background-color:white; color:rgb(0, 0, 0)" ;>
                                    <iframe id="widget_autocomplete_preview" width="350" height="600" frameborder="0" src="https://meteofrance.com/widget/prevision/800210"> </iframe>

                                    </div>

                                </div>
                                <!-- If we need navigation buttons -->
                                <div class="swiper-button-prev"></div>
                                <div class="swiper-button-next"></div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </section>

        <?php $day = date("Y-m-d") ?>
        <h2>Consommation du jour : <div id="jour" style="display: inline;"><?php echo $day; ?></div>
        </h2>
        <div id="Graphique"><canvas height="90" id="myChart"></canvas></div>

        <!--screen short section-->

        <section id="screen_area" class="screen_area">
            <div class="container">
                <div class="row">
                    <div class="main_screen">
                        <div class="col-md-8 col-md-offset-2 col-sm-12">
                            <div class="head_title text-center">

                            </div>

                            <!-- JS includes -->

                            <script src="assets/js/vendor/jquery-1.11.2.min.js"></script>
                            <script src="assets/js/vendor/bootstrap.min.js"></script>
                            <script src="assets/js/jquery.magnific-popup.js"></script>
                            <script src="assets/js/jquery.easing.1.3.js"></script>
                            <script src="assets/js/swiper.min.js"></script>
                            <script src="assets/js/jquery.collapse.js"></script>
                            <script src="assets/js/bootsnav.js"></script>
                            <script src="JS/Capteurs.js"></script>
                            <script src="JS/consommation.js"></script>
                            <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
                            <script src="assets/js/plugins.js"></script>
                            <script src="assets/js/main.js"></script>
                        </div>
                    </div>
                </div>
            </div>
        </section>
    </div>
    <select id="minGraph" name="Heure min">
        <option selected disabled>Heure Min</option>
        <?php echo $conso->getHourList($day); ?>
    </select>

    <select id="maxGraph" name="Heure max">
        <option selected disabled>Heure Max</option>
        <?php echo $conso->getHourList($day); ?>
    </select>
    <select id="dateSelected">
        <?php echo $conso->getDateList(); ?>
    </select>
    <button onclick="setIntervalGraph()">Filtrer la date</button>
</body>

</html>

<script>
    //Déclaration des variables.
    var ctx = document.getElementById('myChart');
    var chart = new Chart(ctx, {
        // Le type de graphique
        type: 'bar',
        // Les données
        data: {
            labels: [<?php echo $conso->getOnlyOneDate($day); ?>],
            datasets: [{
                    label: 'Consommation en eau courante en fonction du temps',
                    backgroundColor: 'rgb(51, 209, 255)',
                    borderColor: 'rgb(51, 209, 255)',
                    data: [<?php echo $conso->getWaterConsoCourante(); ?>]
                },
                {
                    label: 'Consommation électique en fonction du temps',
                    backgroundColor: 'rgb(243, 255, 0)',
                    borderColor: 'rgb(243, 255, 0)',
                    data: [<?php echo $conso->getConsoElec(); ?>]
                },
                {
                    label: 'Consommation en eau de pluie en fonction du temps',
                    backgroundColor: 'rgb(51, 255, 249)',
                    borderColor: 'rgb(51, 255, 249)',
                    data: [<?php echo $conso->getWaterConsoPluie(); ?>]
                }
            ]
        },
        // Configuration options go here
        options: {
            scales: {
                x: {
                    min: 0,
                    max: 24
                }
            }
        }
    });
</script>
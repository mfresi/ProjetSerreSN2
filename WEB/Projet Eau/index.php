
<?php include ("class/capteurs.php");
?>


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



    <!--For Plugins external css-->
    <!--<link rel="stylesheet" href="assets/css/plugins.css" />-->
    <!--Theme custom css -->
    <link rel="stylesheet" href="assets/css/style.css">

    <!--Theme Responsive css-->
    <link rel="stylesheet" href="assets/css/responsive.css" />

    <script src="assets/js/vendor/modernizr-2.8.3-respond-1.4.2.min.js"></script>
</head>

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
                                <h1 class="text-white">ProLaSerre</h1>
                            </div>

                            <div class="home_btns m-top-40">

                            </div>
                        </div>

                        <div class="col-md-6">
                            <div class="phone_one phone_attr1 text-center sm-m-top-50">

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
                                    <img src="assets/1599413451355.jpg">
                                    </div>
                                    <div class="swiper-slide" style="background-color:white; color:rgb(0, 0, 0)" ;>
                                    <img src="assets/1599413451355.jpg">
                                    </div>
                                    <div class="swiper-slide" style="background-color:white; color:rgb(0, 0, 0)" ;>
                                        <img src="assets/1599413451355.jpg">
                                    </div>
                                    <div class="swiper-slide" style="background-color:white; color:rgb(0, 0, 0)" ;>
                                    <img src="assets/1599413451355.jpg">

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
        <div id="Graphique"><canvas id="myChart"></canvas></div>

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
                            <script src="https://cdn.jsdelivr.net/npm/chart.js@2.8.0"></script>
                            <script src="assets/js/plugins.js"></script>
                            <script src="assets/js/main.js"></script>

                        </div>  
                    </div>
                </div>
            </div>
        </section>
    </div>

</html>

<script>
    //Déclaration des variables.

    var ctx = document.getElementById('myChart').getContext('2d');
    var chart = new Chart(ctx, {
        // Le type de graphique
        type: 'line',

        // Les données
        data: 
        {
            labels: ['Janvier', 'Fevrier', 'Mars', 'Avril', 'Mai', 'Juin', 'Juillet', 'Aout', 'Septembre', 'Octobre', 'Novembre', 'Decembre'],
            datasets: 
            [{
                label: 'Consommation eau de pluie en fonction du temps',
                backgrounColor: 'rgb(255, 99, 132)',
                borderColor: 'rgb(255, 99, 132)',
                data: [1,5,7,6,19,5,5,5,11,30,40,0,17,10]
            },
            {
                label: 'Consommation eau courante en fonction du temps',
                backgroundColor: 'rgb(100, 155, 188)',
                borderColor: 'rgb(100, 155, 188)',
                data: [10,15,13,1,18,7,4,0,5,20,6,14,20]
            }
            ]   
        },

        // Configuration options go here
        options: {}
    });
</script>

<?php 
    $conso = new capteurs;

    $conso->getWaterConsoPluie();
    $conso->getWaterConsoCourante();
    $conso->getConsoElec();
?>

<?php

    class capteurs
    {
        private $_eau_pluie;
        private $_eau_courante;
        private $_bdd;
    
        public function __construct()
        {
      
    $this->_bdd = new PDO('mysql:host=192.168.65.54;dbname=Serre', 'root', 'root');

        }
        
        public function getWaterConsoPluie()
        {
            $conso = $this->_bdd->query('SELECT `eau_pluie` FROM `consommation`');
            while($tabConso = $conso->fetch())
            {
                echo ($tabConso['eau_pluie']);
            }
            
        }

        public function getWaterConsoCourante()
        {
            $conso = $this->_bdd->query('SELECT `eau_courante` FROM `consommation`');
            while($tabConso = $conso->fetch())
            {
                echo ($tabConso['eau_courante']);
            }
            
        }

        
    }
?>
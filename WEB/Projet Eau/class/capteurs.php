<?php

    class capteurs
    {
        private $_eau_pluie;
        private $_eau_courante;
        private $_date;
        private $_elec;
        private $_bdd;

        public function __construct()
        {
            try
            {
                $this->_bdd = new PDO('mysql:host=192.168.1.20;dbname=Serre', 'admin', 'admin');
            }
            catch(Exception $e)
            {
                echo $e->getMessage();
            }
            

        }

        public function envoiConso($eau_pluie, $eau_courante, $elec, $date)
        {
            $conso = $this->_bdd->query("INSERT INTO `consommation`(`eau_pluie`, `eau_courante`, `electrique`, `date`) VALUES (:eau_pluie, :eau_courante, :electrique , :date)");
            $conso->execute([
                'eau_pluie' => $eau_pluie,
                'eau_courante' => $eau_courante,
                'electrique' => $elec,
                'date' => $date
            ]); 
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
        public function getConsoElec()
        {
            $conso = $this->_bdd->query('SELECT `electrique` FROM `consommation`');
            while($tabConso = $conso->fetch())
            {
                echo ($tabConso['electrique']);
            }
        }
    }
?>
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
                $this->_bdd = new PDO('mysql:host=192.168.65.54;dbname=Serre', 'root', 'root');
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
        
        public function getDate()
        {
            $conso = $this->_bdd->query('SELECT `date` FROM `consommation`');
            while($tabConso = $conso->fetch())
            {
                echo ($tabConso['date'] . ",");
            }
        }
        public function getWaterConsoPluie()
        {
            $conso = $this->_bdd->query('SELECT `eau_pluie` FROM `consommation`');
            while($tabConso = $conso->fetch())
            {
                echo ($tabConso['eau_pluie'] . ",");
            }
        }

        public function getWaterConsoCourante()
        {
            $conso = $this->_bdd->query('SELECT `eau_courante` FROM `consommation`');
            while($tabConso = $conso->fetch())
            {
                echo ($tabConso['eau_courante'] . ",");
            }
        }
        public function getConsoElec()
        {
            $conso = $this->_bdd->query('SELECT `electrique` FROM `consommation`');
            while($tabConso = $conso->fetch())
            {
                echo ($tabConso['electrique'] . ",");
            }
        }

        public function archiveData()
        {
            $conso = $this->_bdd->query("INSERT INTO `test` SELECT * FROM `consommation`");

            if ($conso != false)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public function purgeTable()
        {
            $conso = $this->_bdd->query("TRUNCATE TABLE `consommation`");
        }

        public function displayArchivage()
        {   
            $conso = $this->_bdd->query("SELECT * FROM `test` ORDER BY `date` DESC");

            while($tabConso = $conso->fetch())
            { ?>
                <table border="1">
                    <tr>
                        <td><?php echo $tabConso['eau_pluie'];?></td>
                        <td><?php echo $tabConso['eau_courante'];?></td>
                        <td><?php echo $tabConso['electrique'];?></td>
                    </tr> 
                </table><?php
            }
        }

        public function insertBDDConso($eau_pluie, $eau_courante, $electrique, $date)
        {
            $conso = $this->_bdd->query('INSERT INTO `consommation`(`eau_pluie`, `eau_courante`, `electrique`, `date`) VALUES ("' . $eau_pluie . '", "' . $eau_courante . '", "' . $electrique . '", "' . $date . '")');

            if ($conso == true)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
?>
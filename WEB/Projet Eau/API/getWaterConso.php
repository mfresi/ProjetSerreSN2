 <? function getWaterConsoCourante()
    {
        $conso = $this->_bdd->query('SELECT `eau_courante` FROM `consommation`');
        while ($tabConso = $conso->fetch()) {
            echo ($tabConso['eau_courante'] . ",");
        }
    }
    ?>
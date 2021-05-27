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
        try {
            $this->_bdd = new PDO('mysql:host=192.168.65.54;dbname=Serre', 'root', 'root');
        } catch (Exception $e) {
            echo $e->getMessage();
        }
    }

    /* public function envoiConso($eau_pluie, $eau_courante, $elec, $date)
    {
        $conso = $this->_bdd->query("INSERT INTO `consommation`(`eau_pluie`, `eau_courante`, `electrique`, `date`) VALUES (:eau_pluie, :eau_courante, :electrique , :date)");
        $conso->execute([
            'eau_pluie' => $eau_pluie,
            'eau_courante' => $eau_courante,
            'electrique' => $elec,
            'date' => $date
        ]);
    } */
    public function getHour()
    {
        $conso = $this->_bdd->query('SELECT `heure` FROM `consommation` ORDER BY `id_consommation` DESC');
        while ($tabConso = $conso->fetch()) {
            echo ($tabConso['heure'] . ",");
        }
    }
    public function getWaterConsoPluie()
    {
        $conso = $this->_bdd->query('SELECT `eau_pluie` FROM `consommation` ORDER BY `id_consommation` DESC');
        while ($tabConso = $conso->fetch()) {
            echo ($tabConso['eau_pluie'] . ",");
        }
    }
    public function getWaterConsoCourante()
    {
        $conso = $this->_bdd->query('SELECT `eau_courante` FROM `consommation` ORDER BY `id_consommation` DESC');
        while ($tabConso = $conso->fetch()) {
            echo ($tabConso['eau_courante'] . ",");
        }
    }
    public function getConsoElec()
    {
        $conso = $this->_bdd->query('SELECT `electrique` FROM `consommation` ORDER BY `id_consommation` DESC');
        while ($tabConso = $conso->fetch()) {
            echo ($tabConso['electrique'] . ",");
        }
    }
    public function archiveData()
    {
        $conso = $this->_bdd->query("INSERT INTO archives (eau_pluie, eau_courante, electrique, heure) SELECT eau_pluie, eau_courante, electrique, heure FROM consommation");

        if ($conso != false) {
            return true;
        } else {
            return false;
        }
    }
    public function purgeTable()
    {
        $conso = $this->_bdd->query("TRUNCATE TABLE `consommation`");
    }

    public function displayArchivage()
    {
        $conso = $this->_bdd->query("SELECT * FROM `archives` ORDER BY `id_consommation` DESC");
?> <?php
        while ($tabConso = $conso->fetch()) { ?>
            <table>
                <th>Conso Eau Pluie</th>
                <th>Conso Eau Courante</th>
                <th>Conso Electrique</th>
                <th>Heure</th>
                <tr>
                    <td><?php echo $tabConso['eau_pluie']; ?></td>
                    <td><?php echo $tabConso['eau_courante']; ?></td>
                    <td><?php echo $tabConso['electrique']; ?></td>
                    <td><?php echo $tabConso['heure']; ?></td>
                </tr>
            </table> <?php
                    }
                }

                public function insertBDDConso($eau_pluie, $eau_courante, $electrique, $date)
                {
                    $conso = $this->_bdd->query('INSERT INTO `consommation`(`eau_pluie`, `eau_courante`, `electrique`, `heure`) VALUES ("' . $eau_pluie . '", "' . $eau_courante . '", "' . $electrique . '", "' . $date . '")');

                    if ($conso == true) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }

                        ?>

<style>
    table {
        border-collapse: collapse;
        width: 100%;
        border: 1px solid #ddd;
    }

    th,
    td {
        text-align: left;
        padding: 8px;
    }

    tr:nth-child(even) {
        background-color: #f2f2f2;
    }
</style>
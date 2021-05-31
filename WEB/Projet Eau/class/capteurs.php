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
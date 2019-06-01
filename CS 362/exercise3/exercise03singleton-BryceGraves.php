<?php
class Sky
{
    private static $_instance;
    private static $_instanceCount = 0;
    private static $_id;

    public static function getInstance()
    {
        if (!isset(self::$_instance)) {
            self::$_instance = new Sky;
            self::$_instanceCount += 1;
            self::$_id = self::$_instanceCount;
        }
        return self::$_instance;
    }

    public function __toString()
    {
        return "I am sky object " . self::$_id . " of " .
               self::$_instanceCount .
               " total instances.\n";
    }

}

$sky = Sky::getInstance();
echo $sky;
$anotherSky = Sky::getInstance();
echo $anotherSky;
$bloodRedSky = Sky::getInstance();
echo $bloodRedSky;
$pinkSky = Sky::getInstance();
echo $pinkSky;

?>

// Bryce Graves

<?php
class IceBoxRefrigerator {
    public $height, $width, $depth;
    public function add($beverage) { }
}

class BrokenRefrigerator {
    public $height, $width, $depth;
    public function add($beverage) { }
}

class RootBeer { }
class Kombucha { }

class Kitchen {

    private $refrigerator;

    public function __construct($refrigerator) {
        $this->refrigerator = $refrigerator;
    }

    #Not sure if this is the best way to achieve this
    public function addBeverage($beverage) {
        $this->refrigerator->add( $beverage );
    }

    public function addBeerToRefrigerator() {
        $this->refrigerator->add( new RootBeer() );
    }

    public function __toString() {
        $fridgeVolume = ($this->refrigerator->height * $this->refrigerator->width * $this->refrigerator->depth);
        $fridgeVolumeGallons = $fridgeVolume * 7.48052;
        return "Kitchen. Fridge volume = " . $fridgeVolumeGallons . " gallons";
    }

}

// Current usage example:

$kitchen = new Kitchen(new BrokenRefrigerator);
$kitchen->addBeverage(new Kombucha);
$kitchen->addBeerToRefrigerator();
echo (string)$kitchen;

// $kitchen has an IceBoxRefrigerator with a RootBeer in it.

// Problem: you can't create a kitchen with a different fridge, and you can't
//          add any beverage other than beer.

// Goal: Create a kitchen with a BrokenRefrigerator, and add Kombucha to it.

?>


abstract class Beast {

  Beast(String name) {
    this.name = name;
  }

  void speak() {

  }

  abstract void suffix();
}

interface Speakable {
  void speak();
}

class Troll implements Speakable extends Beast {
  void speak() {
  }

  void suffix() {

  }
}

class Unicorn implements Speakable extends Beast {
  void speak() {
  }

  void suffix() {

  }
}

Beast b = new Beast(); //compile error

vector<Beast> beasts;
beasts.add(new Troll());
beasts.add(new Unicorn());

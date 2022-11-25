public class Main {
  public static void main(String[] args) {
    Employee technicalWriter = new TechnicalWriter("Mark", 50000, 4, 2);
    System.out.println(technicalWriter.toString());
    System.out.println();
    Employee engineer = new Engineer("Natashia", 50000, 7, 2);
    System.out.println(engineer.toString());
    System.out.println();
    Employee productManager = new ProductManager("Carlos", 50000, 8, 5);
    System.out.println(productManager.toString());
    System.out.println();

    Owner owner = new Owner();
    owner.addEmployee(technicalWriter);
    owner.addEmployee(engineer);
    owner.addEmployee(productManager);

    System.out.println("We be here");

    System.out.println(owner.toString());
    owner.giveRaise(Employee.class, .25);
    // owner.giveRaise(TechnicalWriter.class,.25);
    // owner.giveRaise(Engineer.class,.25);
    // owner.giveRaise(ProductManager.class, .25);
  }
}

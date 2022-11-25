import java.util.ArrayList;

public class Owner extends Employee {
  ArrayList<Employee> owner = new ArrayList<>();

  public Owner() {
  }

  public void addEmployee(Employee employee) {
    owner.add(employee);
  }

  @Override
  public String toString() {
    return "" + owner;
  }

  public void giveRaise(Class<?> Employee, double raisePercentage) {
    // enhanced for loop
    for (Employee item : owner) {
      if (item.getClass().equals("Engineer")) {
        System.out.println("We made it");
      }
      System.out.println(item.getClass());
    }
  }
}

/**
 * I made a giveRaise method that takes in the class and feed it a
 * percentageRaise argument The signature looks like this void
 * giveRaise(Class<?> className , double percentRaise) from there we used an
 * enhanced for loop of the dataType object (Employee in my case) and had it
 * take items out of the arraylist and assign them to an employee variable. then
 * i created an if statement that verifys a match (==) between my
 * employee.getClass() and the className
 */

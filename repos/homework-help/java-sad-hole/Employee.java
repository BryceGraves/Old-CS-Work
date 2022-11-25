/**
 * Employee.java - Employee Benefits Management
 * 
 * @author Your Name
 * @version 1
 */
public class Employee {
  private String name;
  private double baseSalary;
  private int yearsOfExperience;
  private int yearsAtCompany;
  protected final static int YEARS_AT_COMPANY_MAX_VACATION_THRESHOLD = 2;
  protected final static int YEARS_AT_COMPANY_MIN_VACATION_THRESHOLD = 1;

  /**
   * Parameterless constructor
   */
  public Employee() {
    this("", 0, 0, 0);
  }

  /**
   * Parameterized constructor
   * 
   * @param name              A variable of type String
   * @param baseSalary        A variable of type double
   * @param yearsOfExperience A variable of type int
   * @param yearsAtCompany    A variable of type int
   */
  public Employee(String name, double baseSalary, int yearsOfExperience, int yearsAtCompany) {
    this.name = name;
    this.baseSalary = baseSalary;
    this.yearsOfExperience = yearsOfExperience;
    this.yearsAtCompany = yearsAtCompany;
  }

  // Accessor methods
  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public double getBaseSalary() {
    return baseSalary;
  }

  public void setBaseSalary(double baseSalary) {
    this.baseSalary = baseSalary;
  }

  public int getYearsOfExperience() {
    return yearsOfExperience;
  }

  public void setYearsOfExperience(int yearsOfExperience) {
    this.yearsOfExperience = yearsOfExperience;
  }

  public int getYearsAtCompany() {
    return yearsAtCompany;
  }

  public void setYearsAtCompany(int yearsAtCompany) {
    this.yearsAtCompany = yearsAtCompany;
  }

  /**
   * Returns the employees name, salary and motto
   * 
   * @return A value of data type String
   */
  @Override
  public String toString() {
    return "Employee name: " + name + ", baseSalary: $" + getBaseSalary() + "\nmotto: " + motto();
  }

  /**
   * Returns a generic employee motto
   * 
   * @return A value of data type String
   */
  public String motto() {
    return "We value our employees";
  }

}
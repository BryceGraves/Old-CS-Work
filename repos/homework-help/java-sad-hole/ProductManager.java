public class ProductManager extends Employee {
  private final static int SALARY_MULTIPLIER = 2;
  private final static int SHARES_PER_YEAR = 100;
  private final static int VACATION_MAX = 4;
  private final static int VACATION_MIN = 3;

  public ProductManager() {
    super();
  }

  public ProductManager(String name, double baseSalary, int yearsOfExperience, int yearsAtCompany) {
    super(name, baseSalary * SALARY_MULTIPLIER, yearsOfExperience, yearsAtCompany);
  }

  public int vacationTime() {
    int vacationTime = 0;
    if (getYearsAtCompany() >= YEARS_AT_COMPANY_MAX_VACATION_THRESHOLD) {
      vacationTime = VACATION_MAX;
    } else if (getYearsAtCompany() >= YEARS_AT_COMPANY_MIN_VACATION_THRESHOLD) {
      vacationTime = VACATION_MIN;
    }
    return vacationTime;
  }

  // @Override
  // public double getBaseSalary() {
  // return getBaseSalary();
  // }

  public int stockOptions() {
    return getYearsAtCompany() * SHARES_PER_YEAR;
  }

  @Override
  public String motto() {
    return "There is nothing so useless as doing efficiently that which should not be done at all.";
  }

  @Override
  public String toString() {
    return super.toString() + "\nVacation time: " + vacationTime() + " weeks" + ". Stock Options: " + stockOptions()
        + " shares";
  }
}
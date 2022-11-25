public class TechnicalWriter extends Employee {
  private final static int VACATION_MAX = 2;
  private final static int VACATION_MIN = 1;

  public TechnicalWriter() {
    super();
  }

  public TechnicalWriter(String name, double baseSalary, int yearsOfExperience, int yearsAtCompany) {
    super(name, baseSalary, yearsOfExperience, yearsAtCompany);
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

  @Override
  public String motto() {
    return "You can always edit a bad page. You can’t edit a blank page";
  }

  @Override
  public String toString() {
    return super.toString() + "\nVacation time: " + vacationTime() + " weeks";
  }
}

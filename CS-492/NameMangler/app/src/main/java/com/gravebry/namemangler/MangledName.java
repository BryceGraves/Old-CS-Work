package com.gravebry.namemangler;

import java.util.Random;

public class MangledName {

  private String firstName, lastName;

  private Boolean isNice;

  public MangledName() {
      firstName = lastName = "";
      isNice = false;
  }

  private String getNicePrepend() {
    String[] prepends = {
      "Awesome",
      "Amazing",
      "Best",
      "Good",
      "Great"
    };

    int selection = new Random().nextInt(prepends.length);

    return prepends[selection];
  }

  private String getRudePrepend() {
    String[] prepends = {
            "Bad",
            "Terrible",
            "Baddest",
            "Worst",
            "Evil"
    };

    int selection = new Random().nextInt(prepends.length);

    return prepends[selection];
  }

  public void mangleName() {
    if (isNice) {
      lastName = getNicePrepend();
    } else {
      lastName = getRudePrepend();
    }
  }

  public String getFullName() {
    return firstName + " " + lastName;
  }

  public String getFirstName() {
    return firstName;
  }

  public void setFirstName(String newName) {
    firstName = newName;
  }

  public String getLastName() {
    return lastName;
  }

  public void setLastName(String newName) {
    lastName = newName;
  }

  public void setIsNice(Boolean isNice) {
    this.isNice = isNice;
  }

  public Boolean getIsNice() {
    return isNice;
  }
}

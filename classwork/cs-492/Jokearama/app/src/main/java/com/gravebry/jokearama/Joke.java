package com.gravebry.jokearama;

public class Joke {

  private int currentLine, index;
  private String title;
  private boolean  touched;
  private String[] lines;

  public Joke(int index) {
    this.index = index;
    lines = JokeGenerator.getJokeStrings();
    currentLine = 0;
  }

  public int getIndex() {
    return index;
  }

  public String getTitle() {
    return title;
  }

  public void setTitle(String title) {
    this.title = title;
  }

  public void setTouched(boolean touched) {
    this.touched = touched;
  }

  public boolean isTouched() {
    return touched;
  }

  public void setCurrentLine(int currentLine) {
    this.currentLine = currentLine;
  }

  public int getCurrentLine() {
    return currentLine;
  }

  public String getLine(int index) {
    return lines[index];
  }
}

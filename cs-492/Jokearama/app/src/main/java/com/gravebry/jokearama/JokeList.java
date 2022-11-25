package com.gravebry.jokearama;

import android.content.Context;

import java.util.ArrayList;
import java.util.List;

public class JokeList {
  private static JokeList jokeList;
  private List<Joke> jokes;

  private int viewedJokeTotal;

  private int TOTAL_JOKES = 20;

  public static JokeList get(Context context) {
    if (jokeList == null) {
      jokeList = new JokeList(context);
    }

    return jokeList;
  }

  private JokeList(Context context) {
    jokes = new ArrayList<>();
    for (int i = 0; i < TOTAL_JOKES; i++) {
      Joke joke = new Joke(i);
      joke.setTitle("Joke " + (i + 1));
      jokes.add(joke);
    }

    viewedJokeTotal = 0;
  }

  public List<Joke> getJokes() {
    return jokes;
  }

  public Joke getJoke(int index) {
    return jokes.get(index);
  }

  public void jokeTouched(int index) {
    viewedJokeTotal++;
    getJoke(index).setTouched(true);
  }

  public int getViewedJokeTotal() {
    return viewedJokeTotal;
  }

  public void resetJokes() {
    for (Joke joke : jokes) {
      joke.setTouched(false);
      joke.setCurrentLine(0);
    }

    viewedJokeTotal = 0;
  }
}

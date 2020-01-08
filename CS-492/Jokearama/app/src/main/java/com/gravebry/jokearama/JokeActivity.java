package com.gravebry.jokearama;

import android.content.Context;
import android.content.Intent;

import androidx.fragment.app.Fragment;

import java.util.UUID;

public class JokeActivity extends SingleFragmentActivity {

  private static final String EXTRA_JOKE_INDEX =
      "com.gravebry.jokearama.joke_index";

  public static Intent newIntent(Context packageContext, int jokeIndex) {
    Intent intent = new Intent(packageContext, JokeActivity.class);
    intent.putExtra(EXTRA_JOKE_INDEX, jokeIndex);
    return intent;
  }

  @Override
  protected Fragment createFragment() {
    int jokeIndex = getIntent().getIntExtra(EXTRA_JOKE_INDEX, 0);
    return JokeFragment.newInstance(jokeIndex);
  }
}

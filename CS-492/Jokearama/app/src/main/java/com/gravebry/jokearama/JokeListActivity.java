package com.gravebry.jokearama;

import androidx.fragment.app.Fragment;

public class JokeListActivity extends SingleFragmentActivity {

  @Override
  protected Fragment createFragment() {
    return new JokeListFragment();
  }
}
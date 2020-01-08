package com.gravebry.namemangler;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MangledNameActivity extends AppCompatActivity {

  private static final String EXTRA_FIRST_NAME = "com.gravebry.namemangler.first_name";
  private static final String EXTRA_IS_NICE = "com.gravebry.namemangler.is_nice";
  private static final String KEY_MANGLED_NAME = "mangled_name";

  private TextView mangledNameTextView;
  private Button resetButton, reMangleButton;
  private MangledName mangledName = new MangledName();

  private Boolean isNice;
  private ImageView goodImage;
  private ImageView badImage;


  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_mangled);

    mangledNameTextView = findViewById(R.id.mangled_name);
    resetButton = findViewById(R.id.reset_button);
    reMangleButton = findViewById(R.id.re_mangle_button);
    goodImage = findViewById(R.id.good_image);
    badImage = findViewById(R.id.bad_image);

    if (savedInstanceState != null) {
      String[] savedName = savedInstanceState.getStringArray(KEY_MANGLED_NAME);

      if (savedName.length < 2) { return; }

      mangledName.setFirstName(savedName[0]);
      mangledName.setLastName(savedName[1]);
    } else {
      mangledName.setFirstName(getIntent().getStringExtra(EXTRA_FIRST_NAME));
      mangledName.setIsNice(getIntent().getBooleanExtra(EXTRA_IS_NICE, false));
      mangledName.mangleName();
    }

    if (mangledName.getIsNice()) {
        badImage.setVisibility(View.INVISIBLE);
    } else {
        goodImage.setVisibility(View.INVISIBLE);
    }

    mangledNameTextView.setText(mangledName.getFullName());

    resetButton.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View v) {
        finish();
      }
    });

    reMangleButton.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View v) {
        mangledName.mangleName();
        mangledNameTextView.setText(mangledName.getFullName());
      }
    });
  }

  @Override
  public void onSaveInstanceState(Bundle savedInstanceState) {
    super.onSaveInstanceState(savedInstanceState);

    String[] savedName = {mangledName.getFirstName(), mangledName.getLastName()};
    savedInstanceState.putStringArray(KEY_MANGLED_NAME, savedName);
  }

  public static Intent newIntent(Context packageContext, String nameText, Boolean isNice) {
    Intent intent = new Intent(packageContext, MangledNameActivity.class);
    intent.putExtra(EXTRA_FIRST_NAME, nameText);
    intent.putExtra(EXTRA_IS_NICE, isNice);
    return intent;
  }
}

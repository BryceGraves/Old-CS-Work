package com.gravebry.namemangler;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

  private Button mangleNicelyButton, mangleRudelyButton;
  private EditText nameInput;

  private static final int REQUEST_CODE_MANGLE = 0;

  @Override
  protected void onActivityResult(int requestCode, int resultCode, Intent data) {
    super.onActivityResult(requestCode, resultCode, data);
    nameInput.getText().clear();
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    
    nameInput = findViewById(R.id.name_input);

    mangleNicelyButton = findViewById(R.id.mangle_nicely_button);
    mangleRudelyButton = findViewById(R.id.mangle_rudely_button);

    mangleNicelyButton.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View v) {
        // Verify Name is Present
        if (nameInput.getText().length() <= 0) {
          Toast toast = Toast.makeText(getApplicationContext(), R.string.no_name, Toast.LENGTH_SHORT);
          toast.setGravity(Gravity.BOTTOM, 0,180);
          toast.show();
          return;
        }

        // Start Mangled Name Activity
        Intent intent = MangledNameActivity.newIntent(getApplicationContext(), nameInput.getText().toString(), true);
        startActivityForResult(intent, REQUEST_CODE_MANGLE);
      }
    });

    mangleRudelyButton.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View v) {
        // Verify Name is Present
        if (nameInput.getText().length() <= 0) {
          Toast toast = Toast.makeText(getApplicationContext(), R.string.no_name, Toast.LENGTH_SHORT);
          toast.setGravity(Gravity.BOTTOM, 0,180);
          toast.show();
          return;
        }

        // Start Mangled Name Activity
        Intent intent = MangledNameActivity.newIntent(getApplicationContext(), nameInput.getText().toString(), false);
        startActivityForResult(intent, REQUEST_CODE_MANGLE);
      }
    });
  }
}

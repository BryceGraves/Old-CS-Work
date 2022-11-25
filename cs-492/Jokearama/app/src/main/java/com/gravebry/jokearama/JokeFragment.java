package com.gravebry.jokearama;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;

import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;

import java.util.List;

public class JokeFragment extends Fragment {

  private static final String ARG_JOKE_INDEX = "joke_index";

  private Joke joke;

  private ImageButton imageButton;
  private TextView firstLine, secondLine, thirdLine, forthLine, fifthLine, subtitle;
  private int buttonOff, buttonOn;

  public static JokeFragment newInstance(int jokeIndex) {
    Bundle args = new Bundle();
    args.putInt(ARG_JOKE_INDEX, jokeIndex);

    JokeFragment fragment = new JokeFragment();
    fragment.setArguments(args);
    return fragment;
  }

  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
  }

  @Override
  public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
    View view = inflater.inflate(R.layout.fragment_joke, container, false);
    final FragmentActivity activity = getActivity();

    int jokeIndex = getArguments().getInt(ARG_JOKE_INDEX);

    final JokeList jokeList = JokeList.get(activity);
    List<Joke> jokes = jokeList.getJokes();
    joke = jokeList.getJoke(jokeIndex);

    String subtitleText = jokes.size() + " jokes, " + jokeList.getViewedJokeTotal() + " completed";

    subtitle = activity.findViewById(R.id.app_sub_title);
    subtitle.setText(subtitleText);

    firstLine = view.findViewById(R.id.first_line);
    secondLine = view.findViewById(R.id.second_line);
    thirdLine = view.findViewById(R.id.third_line);
    forthLine = view.findViewById(R.id.fourth_line);
    fifthLine = view.findViewById(R.id.fifth_line);

    populateJokeLines(joke.getCurrentLine());

    final DialogInterface.OnClickListener dialogClickListener = new DialogInterface.OnClickListener() {
      @Override
      public void onClick(DialogInterface dialog, int which) {
        switch (which){
          case DialogInterface.BUTTON_POSITIVE:
            JokeList jokeList = JokeList.get(getActivity());
            List<Joke> jokes = jokeList.getJokes();
            jokeList.resetJokes();

            imageButton.setImageDrawable(getResources().getDrawable(buttonOff));

            String subtitleText = jokes.size() + " jokes, " + jokeList.getViewedJokeTotal() + " completed";
            subtitle.setText(subtitleText);

            depopulateJokeLines();
            break;

          case DialogInterface.BUTTON_NEGATIVE:
            // No button clicked
            break;
        }
      }
    };

    imageButton = activity.findViewById(R.id.imageButton);
    imageButton.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View v) {
        if (jokeList.getViewedJokeTotal() == 0) { return; }

        AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
        builder.setMessage("Reset All Joke Viewings?").setPositiveButton("Yes", dialogClickListener).setNegativeButton("No", dialogClickListener).show();
      }
    });

    buttonOff = getResources().getIdentifier("btn_star_big_off", "drawable", "android");
    buttonOn = getResources().getIdentifier("btn_star_big_on", "drawable", "android");

    imageButton.setImageDrawable(jokeList.getViewedJokeTotal() > 0 ?  getResources().getDrawable(buttonOn) : getResources().getDrawable(buttonOff));

    view.setOnTouchListener(new OnSwipeTouchListener(activity) {
      @Override
      public void onClick() {
        super.onClick();
        int currentLine = joke.getCurrentLine() + 1;

        if (currentLine >= 5) { return; }

        if (currentLine == 4) {
          JokeList jokeList = JokeList.get(getActivity());
          List<Joke> jokes = jokeList.getJokes();
          jokeList.jokeTouched(joke.getIndex());
          imageButton.setImageDrawable(getResources().getDrawable(buttonOn));

          String subtitleText = jokes.size() + " jokes, " + jokeList.getViewedJokeTotal() + " completed";
          subtitle.setText(subtitleText);

          joke.setCurrentLine(currentLine);
          populateJokeLines(currentLine);
          return;
        }

        joke.setCurrentLine(currentLine);
        populateJokeLines(currentLine);
      }

      @Override
      public void onSwipeRight() {
        super.onSwipeRight();
        getActivity().onBackPressed();
      }
    });

    return view;
  }

  // A place of shame and sadness stay away

  public void populateJokeLines(int currentLine) {
    // just stay away from this >.>
    if (currentLine >= 0) { firstLine.setText(joke.getLine(0)); }
    if (currentLine >= 1) { secondLine.setText(joke.getLine(1)); }
    if (currentLine >= 2) { thirdLine.setText(joke.getLine(2)); }
    if (currentLine >= 3) { forthLine.setText(joke.getLine(3)); }
    if (currentLine >= 4) { fifthLine.setText(joke.getLine(4)); }
  }

  public void depopulateJokeLines() {
    // what did I tell you get out of here...
    secondLine.setText("");
    thirdLine.setText("");
    forthLine.setText("");
    fifthLine.setText("");
  }

  public class OnSwipeTouchListener implements View.OnTouchListener {

    private GestureDetector gestureDetector;

    public OnSwipeTouchListener(Context c) {
      gestureDetector = new GestureDetector(c, new GestureListener());
    }

    public boolean onTouch(final View view, final MotionEvent motionEvent) {
      return gestureDetector.onTouchEvent(motionEvent);
    }

    private final class GestureListener extends GestureDetector.SimpleOnGestureListener {

      private static final int SWIPE_THRESHOLD = 100;
      private static final int SWIPE_VELOCITY_THRESHOLD = 100;

      @Override
      public boolean onDown(MotionEvent e) {
        return true;
      }

      @Override
      public boolean onSingleTapUp(MotionEvent e) {
        onClick();
        return super.onSingleTapUp(e);
      }

      @Override
      public boolean onDoubleTap(MotionEvent e) {
        onDoubleClick();
        return super.onDoubleTap(e);
      }

      @Override
      public void onLongPress(MotionEvent e) {
        onLongClick();
        super.onLongPress(e);
      }

      // Determines the fling velocity and then fires the appropriate swipe event accordingly
      @Override
      public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        boolean result = false;
        try {
          float diffY = e2.getY() - e1.getY();
          float diffX = e2.getX() - e1.getX();
          if (Math.abs(diffX) > Math.abs(diffY)) {
            if (Math.abs(diffX) > SWIPE_THRESHOLD && Math.abs(velocityX) > SWIPE_VELOCITY_THRESHOLD) {
              if (diffX > 0) {
                onSwipeRight();
              } else {
                onSwipeLeft();
              }
            }
          } else {
            if (Math.abs(diffY) > SWIPE_THRESHOLD && Math.abs(velocityY) > SWIPE_VELOCITY_THRESHOLD) {
              if (diffY > 0) {
                onSwipeDown();
              } else {
                onSwipeUp();
              }
            }
          }
        } catch (Exception exception) {
          exception.printStackTrace();
        }
        return result;
      }
    }

    public void onSwipeRight() {}
    public void onSwipeLeft() {}
    public void onSwipeUp() {}
    public void onSwipeDown() {}
    public void onClick() {}
    public void onDoubleClick() {}
    public void onLongClick() {}
  }
}

package com.gravebry.jokearama;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.TextView;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class JokeListFragment extends Fragment {
  private RecyclerView jokeRecyclerView;
  private JokeAdapter adapter;

  private ImageButton imageButton;
  private TextView subtitle;
  private int buttonOff, buttonOn;

  @Override
  public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
    View view = inflater.inflate(R.layout.fragment_joke_list, container, false);

    final FragmentActivity activity = getActivity();

    jokeRecyclerView = view.findViewById(R.id.joke_recycler_view);
    jokeRecyclerView.setLayoutManager(new LinearLayoutManager(activity));

    subtitle = activity.findViewById(R.id.app_sub_title);

    final DialogInterface.OnClickListener dialogClickListener = new DialogInterface.OnClickListener() {
      @Override
      public void onClick(DialogInterface dialog, int which) {
        switch (which){
          case DialogInterface.BUTTON_POSITIVE:
            JokeList.get(activity).resetJokes();

            updateUI();
            break;

          case DialogInterface.BUTTON_NEGATIVE:
            break;
        }
      }
    };

    imageButton = activity.findViewById(R.id.imageButton);
    imageButton.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View v) {
        if (JokeList.get(getContext()).getViewedJokeTotal() == 0) { return; }

        AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
        builder.setMessage("Reset All Joke Viewings?").setPositiveButton("Yes", dialogClickListener).setNegativeButton("No", dialogClickListener).show();
      }
    });

    buttonOff = getResources().getIdentifier("btn_star_big_off", "drawable", "android");
    buttonOn = getResources().getIdentifier("btn_star_big_on", "drawable", "android");


    updateUI();

    return view;
  }

  @Override
  public void onResume() {
    super.onResume();
    updateUI();
  }

  private void updateUI() {
    JokeList jokeList = JokeList.get(getActivity());
    List<Joke> jokes = jokeList.getJokes();
    String subtitleText = jokes.size() + " jokes, " + jokeList.getViewedJokeTotal() + " completed";

    subtitle.setText(subtitleText);
    imageButton.setImageDrawable(jokeList.getViewedJokeTotal() > 0 ?  getResources().getDrawable(buttonOn) : getResources().getDrawable(buttonOff));

    if (adapter == null) {
      adapter = new JokeAdapter(jokes);
      jokeRecyclerView.setAdapter(adapter);
    } else {
      adapter.notifyDataSetChanged();
    }
  }

  private class JokeHolder extends RecyclerView.ViewHolder
      implements View.OnClickListener {

    private Joke joke;

    private TextView mTitleTextView;

    public JokeHolder(LayoutInflater inflater, ViewGroup parent) {
      super(inflater.inflate(R.layout.list_item_joke, parent, false));
      itemView.setOnClickListener(this);

      mTitleTextView = itemView.findViewById(R.id.list_joke_label);
    }

    public void bind(Joke joke) {
      this.joke = joke;
      mTitleTextView.setText(joke.getTitle());
      mTitleTextView.setBackgroundColor(joke.isTouched() ? Color.LTGRAY : Color.TRANSPARENT);
    }

    @Override
    public void onClick(View view) {
      Intent intent = JokeActivity.newIntent(getActivity(), joke.getIndex());
      startActivity(intent);
    }
  }

  private class JokeAdapter extends RecyclerView.Adapter<JokeHolder> {

    private List<Joke> jokes;

    public JokeAdapter(List<Joke> jokes) {
      this.jokes = jokes;
    }

    @Override
    public JokeHolder onCreateViewHolder(ViewGroup parent, int viewType) {
      LayoutInflater layoutInflater = LayoutInflater.from(getActivity());
      return new JokeHolder(layoutInflater, parent);
    }

    @Override
    public void onBindViewHolder(JokeHolder holder, int position) {
      Joke joke = jokes.get(position);
      holder.bind(joke);
    }

    @Override
    public int getItemCount() {
      return jokes.size();
    }
  }
}

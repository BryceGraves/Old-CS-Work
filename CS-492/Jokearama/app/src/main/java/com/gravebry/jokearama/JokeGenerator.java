package com.gravebry.jokearama;

import java.util.Random;

public class JokeGenerator {

  public static String[] getJokeStrings() {
    String[][] masterJokeList = {
      { "Knock Knock", "Who's there?", "Ice cream.",    "Ice cream who?", "Ice cream if you don't let me in!" },
      { "Knock Knock", "Who's there?", "Noah.",         "Noah who?",      "Noah way to open the door?" },
      { "Knock Knock", "Who's there?", "Cows go.",      "Cows go who?",   "No, cows go moo!" },
      { "Knock Knock", "Who's there?", "Hatch.",        "Hatch who?",     "Bless you and please cover your mouth next time." },
      { "Knock Knock", "Who's there?", "Boo.",          "Boo who?",       "Don't cry, it's just a joke." },
      { "Knock Knock", "Who's there?", "Venice.",       "Venice who?",    "Venice this door gonna open?" },
      { "Knock Knock", "Who's there?", "Lettuce.",      "Lettuce who?",   "Lettuce in!" },
      { "Knock Knock", "Who's there?", "Scold.",        "Scold who?",     "Scold outside—let me in!" },
      { "Knock Knock", "Who's there?", "Needle.",       "Needle who?",    "Needle little help gettin’ in the door." },
      { "Knock Knock", "Who's there?", "Nana.",         "Nana who?",      "Nana your business who’s there." },
      { "Knock Knock", "Who's there?", "Isabelle.",     "Isabelle who?",  "Isabelle working, or should I keep knocking?" },
      { "Knock Knock", "Who's there?", "Claire.",       "Claire who?",    "Claire the way; I’m coming in!" },
      { "Knock Knock", "Who's there?", "Ben.",          "Ben who?",       "Ben knocking for 20 minutes!" },
      { "Knock Knock", "Who's there?", "Tuna.",         "Tuna who?",      "Tuna piano and it'll sound better!" },
      { "Knock Knock", "Who's there?", "Snow.",         "Snow who?",      "Snow use, I've forgotten my key again!" }
    };

    int index = new Random().nextInt(masterJokeList.length);

    return masterJokeList[index];
  }
}

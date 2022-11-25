/**
 *
 * <h1>Run Length Encoder</h1>
 *
 * <a href="https://en.wikipedia.org/wiki/Run-length_encoding"></a>Run-length
 * Encoding</a> (RLE) has been around since the 1967, and while it isn't as used
 * today in place of better encoders, it is still used as part of those
 * encoders. In this assignment, you will develop a run-length encoder and
 * decoder for Strings.
 *
 * @author YOUR NAME <br>
 *         YOUR EMAIL <br>
 *         Computer Science Department <br>
 *         Colorado State University
 * @version 201990
 */
public class RunLengthEncoder {

  /**
   * Warm up activity. Looking at a String, there is a number hidden in the text.
   * 
   * @param message the String that contains the hidden number
   * @return a long as the numbers can be fairly large
   */
  public static long hiddenNumber(String message) {
    return Long.parseLong(message.replaceAll("-?[^\\d]", ""));
  }

  /**
   * expand(char, int) Helper method for {@link #runLengthDecoding(String)} This
   * method generates a String using two parameters. One is a character and the
   * other is an integer. For example, if the character is 'y' and the integer is
   * 4, this method should return the String "yyyy".
   *
   * A public nonstatic method with two parameters, a character and an integer.
   * 
   * @param x     A character representing the character to repeat in the returned
   *              String.
   * @param count integer representing the number of times to repeat the
   *              character.
   * @return A String representing a sequence of characters.
   */
  public static String expand(char x, int count) {
    String output = "";

    for (int i = 0; i < count; i++) {
      output += x;
    }

    return output;
  }

  /**
   * runLengthEncoding(String) This method takes sequences of the same character
   * in a String and represents that sequence as the number of same characters in
   * a row followed by that character. For example, "BBBWWWWWB", becomes "3B5W1B".
   *
   * A public nonstatic method with one String parameter.
   *
   * @param input A String representing the String to encode.
   * @return A String representing the encoded version of the original String.
   */
  public static String runLengthEncoding(String input) {
    String output = "";
    char previousCharacter = input.charAt(0);
    int count = 0;

    for (char currentCharacter : input.toCharArray()) {
      if (previousCharacter == currentCharacter) {
        ++count;
        continue;
      }

      output += count;
      output += previousCharacter;
      previousCharacter = currentCharacter;
      count = 1;
    }

    output += count;
    output += previousCharacter;

    return output;
  }

  /**
   * runLengthDecoding(String) This changes an encoded String back to the format
   * of the source String. For example, "3B2W2B" would become "BBBWWBB".
   *
   * A public nonstatic method with one parameter, a String.
   * 
   * @param s String representing the String to decode.
   * @return A String representing the original format before encoding.
   * @see #expand(char, int)
   */
  public static String runLengthDecoding(String input) {
    String output = "";
    String numericAsString = "";

    char currentCharacter;

    for (int i = 0; i < input.length(); i++) {
      currentCharacter = input.charAt(i);

      Boolean digit = Character.isDigit(currentCharacter);

      if (digit) {
        numericAsString += currentCharacter;
      } else {
        output += expand(currentCharacter, Integer.parseInt(numericAsString));
        numericAsString = "";
      }
    }

    return output;
  }
}

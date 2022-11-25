/**
 *
 * Tests are often ran in a separate file. This file is just here to help run
 * test on the RunLengthEncoder library that you are working on in
 * RunLengthEncoder.java
 *
 * @author YOUR NAME <br>
 *         YOUR EMAIL <br>
 *         Computer Science Department <br>
 *         Colorado State University
 * @version 2019190
 */

public class TestRunLength {

  /**
   * A tests method that helps test encoding and decoding, also practices with
   * printf
   */
  public static void unitTest() {
    String encodedDNA = RunLengthEncoder.runLengthEncoding(DNA);
    String encodedIMAGE = RunLengthEncoder.runLengthEncoding(IMAGE);

    System.out.print(
        formattedInfo("DNA", DNA.length(), encodedDNA.length(), percentCompression(encodedDNA.length(), DNA.length())));
    System.out.print(formattedInfo("Image", IMAGE.length(), encodedIMAGE.length(),
        percentCompression(encodedIMAGE.length(), IMAGE.length())));

    String decodedDNA = RunLengthEncoder.runLengthDecoding(encodedDNA);
    String decodedIMAGE = RunLengthEncoder.runLengthDecoding(encodedIMAGE);

    System.out.printf("DNA encodes and decodes properly: %b%n", decodedDNA.equals(DNA));
    System.out.printf("IMAGE encodes and decodes properly: %b%n", decodedIMAGE.equals(IMAGE));

  }

  /**
   * Uses String.format to have a very specific format returned. Includes a
   * newline.
   * 
   * For example
   * 
   * <pre>
   *      DNA raw length is 980 while encoded DNA length is 673. 31.33% compression.
   * </pre>
   * 
   * @param name          name that goes at the front
   * @param rawLength     the raw length of the string
   * @param encodedLength the encoded length of the string
   * @param compression   the percent of compression
   * @return a formated string
   */
  public static String formattedInfo(String name, int rawLength, int encodedLength, double compression) {
    return ""; // STUDENT TODO
  }

  /**
   * Support method used in the tests
   * 
   * @param numerator   a double that is the top half of the fraction
   * @param denominator a double that is the bottom half of the fraction
   * @return a double that is the percentage remaining out of 100
   */
  public static double percentCompression(double numerator, double denominator) {
    return (1 - (numerator / denominator)) * 100.0;
  }

  // very small section of DNA like string
  public static final String DNA = "AAAAGGGTTTAAAAAACCTTTAATTTAAAAATTTTAAAACCCCTTTGGGGXTGGGTTGTTTAAGATAAAA"
      + "GGGTTTAAAAAACCTTTAATTTAAAAATTTTAAAACCCCTTTGGGGXTGGGTTGTTTAAGATAAAAAAAA"
      + "AAAAAACCTTTAATTTAAAAATTTTAAAACCCCTTTGGGGXTGGGTTGTTTAAGATAAAAAAAAGGGTTT"
      + "TAATTTAAAAATTTTAAAACCCCTTTGGGGXTGGGTTGTTTAAGATAAAAAAAAGGGTTTAAAAAACCTT"
      + "GTTTAAAAAACCTTTAATTTAAAAATTTTAAAACCCCTTTGGGGXTGGGTTGTTTAAGATAAAAAAAAGG"
      + "TTTAAAACCCCTTTGGGGXTGGGTTGTTTAAGATAAAAAAAAGGGTTTAAAAAACCTTTAATTTAAAAAT"
      + "ACCTTTAATTTAAAAATTTTAAAACCCCTTTGGGGXTGGGTTGTTTAAGATAAAAAAAAGGGTTTAAAAA"
      + "TTTAATTTAAAAATTTTAAAACCCCTTTGGGGXTGGGTTGTTTAAGATAAAAAAAAGGGTTTAAAAAACC"
      + "CTTTAATTTAAAAATTTTAAAACCCCTTTGGGGXTGGGTTGTTTAAGATAAAAAAAAGGGTTTAAAAAAC"
      + "TTAAAACCCCTTTGGGGXTGGGTTGTTTAAGATAAAAAAAAGGGTTTAAAAAACCTTTAATTTAAAAATT"
      + "TTGGGGXTGGGTTGTTTAAGATAAAAAAAAGGGTTTAAAAAACCTTTAATTTAAAAATTTTAAAACCCCT"
      + "TTAAAACCCCTTTAAAACCCCTAAAAAAAAGGGTTTAAAAAACCTTTAATTTAAAAATTTTAAAACCCCT"
      + "AAGATAAAAAAAAGGGTTTAAAAAACCTTTAATTTAAAAATTTTAAAACCCCTTTGGGGXTGGGTTGTTT"
      + "AAGGGTTTAAAAAACCTTTAATTTAAAAATTTTAAAACCCCTTTGGGGXTGGGTTGTTTAAGATAAAAAA";

  // this could actually be loaded via file! (something to think about)
  public static final String IMAGE = "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n"
      + "WWWWWWWWWWWWWWWWWWWWBBWWWWWWWWWWWWWWWWWWWWWW\n" + "WWWWWWWWWWWWWWWWWWWBBWWWWBWWWWWWWWWWWWWWWWWW\n"
      + "WWWWWWWWWWWWWWWWWWBBWWWBBBWWWWWWWWWWWWWWWWWW\n" + "WWWWWWWWWWWWWWWWWBBWWWBBBBWWWWWWWWWWWWWWWWWW\n"
      + "WWWWWWWWWWWWWWWWWBBWWBBBBBWWWWWWWWWWWWWWWWWW\n" + "WWWWWWWWWWWWWWWWWBBWWBBBWWWWWWWWWWWWWWWWWWWW\n"
      + "WWWWWWWWWWWWWWWWWBBWBBWWWWWWWWWWWWWWWWWWWWWW\n" + "WWWWWWWBBBBWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWW\n"
      + "WWWWWBBBBBBBWWWWWBBWWWWWWWWBBBBBBWWWWWWWWWWW\n" + "WWWBBBBBBBBBBBBBBBBBBWWWBBBBBBBBBBBBBBWWWWWW\n"
      + "WWBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBWWWW\n" + "WBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBWWW\n"
      + "WBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBWWW\n" + "WBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBWWW\n"
      + "WBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBWWW\n" + "WBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBWWW\n"
      + "WBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBWWWW\n" + "WBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBWWWWW\n"
      + "WBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBWWWWWW\n" + "WBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBWWWWWWWW\n"
      + "WBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBWWWWWWWWWW\n" + "WBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBWWWWWWWWWWWW\n"
      + "WWBBBBBBBBBBBBWBBBBBBBBBBBBBBWWWWWWWWWWWWWWW\n" + "WWWBBBBBBBBBBWWBBBBBBBBBBBBWWWWWWWWWWWWWWWWW\n"
      + "WWWWWWBBBBWWWWWWWBBBBBBBWWWWWWWWWWWWWWWWWWWW\n" + "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";

  public static void main(String[] args) {
    // uncomment each section after writing the associated method
    System.out.println("hiddenNumber warm-up");
    System.out.println(RunLengthEncoder.hiddenNumber("42"));
    System.out.println(RunLengthEncoder.hiddenNumber("e34e"));
    System.out.println(RunLengthEncoder.hiddenNumber("Johny 5 is Alive."));
    System.out.println(RunLengthEncoder.hiddenNumber("The great robot mystery 101001010012"));
    System.out.println();

    System.out.println("testing expand");
    System.out.println(RunLengthEncoder.expand('w', 3));
    System.out.println(RunLengthEncoder.expand('A', 0));
    System.out.println(RunLengthEncoder.expand('G', 150));
    System.out.println();

    System.out.println("testing runLengthEncoding");
    System.out.println(RunLengthEncoder.runLengthEncoding("RRRRSTTT")); // should return 4R1S3T
    System.out.println(RunLengthEncoder.runLengthEncoding("a")); // should return 1a
    System.out.println(RunLengthEncoder.runLengthEncoding("aa")); // should return 2a
    System.out.println(RunLengthEncoder.runLengthEncoding("aaaaaaaaaaBb")); // should return 10a1B1b
    System.out.println();

    System.out.println("testing runLengthDecoding");
    System.out.println(RunLengthEncoder.runLengthDecoding("4R1S3T")); // should return RRRRSTTT
    System.out.println(RunLengthEncoder.runLengthDecoding("1a")); // should return a
    System.out.println(RunLengthEncoder.runLengthDecoding("2a")); // should return aa
    System.out.println(RunLengthEncoder.runLengthDecoding("10a1B1b")); // should return aaaaaaaaaaBb
    System.out.println();

    // unitTest();
  }
}

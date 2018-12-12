public class two_one_six {
    enum testDataDist {
      RAND_RANGE
        , IN_ORDER      // When using this, the Quick and QuickX can fault on recursion over 64k elements
        , REV_ORDER     // When using this, the QuickNS and Quick3 can fault on recursion over 8k elements
        , NEARLY_SORTED
        , NEARLY_SORTED_REV
    };
    private static final testDataDist TEST_DATA_DIST = testDataDist.NEARLY_SORTED;
    private static final int TEST_ITERATIONS = 1;
    private static final int THOUSAND = 1000;

    //private static final int TEST_LBOUND = 16; // 128K
    private static final int TEST_LBOUND = 16;

    //private static final int TEST_UBOUND = 67000; // ~64 million
    //private static final int TEST_UBOUND = 8192 * 2;
    private static final int TEST_UBOUND = 33 * THOUSAND;

    private static final int NEARLY_LBOUND = 0;
    private static final int NEARLY_UBOUND = 1;

    private static final String FORMAT = "%-11d\t%10.4f\n";
    private static final int SEED = 1796402239;
//    private static final int RANDON_INT_LBOUND = -100 * THOUSAND * THOUSAND;
//    private static final int RANDON_INT_UBOUND = (100 * THOUSAND * THOUSAND) + 1;
    private static final int RANDON_INT_LBOUND = 0;
    private static final int RANDON_INT_UBOUND = 10000;
    private static final boolean SHOW_DATA = false;

    public static void main(String[] args) {

        StdOut.printf("Data set: %s  test iterations %d\n", TEST_DATA_DIST.toString(), TEST_ITERATIONS);

        if (SHOW_DATA) {
            Integer[] values = genDataIntegers(100);

            return;
        }
        StdOut.println("Selection Sort");
        selection();
        StdOut.println("Insertion Sort");
        insertion();
    }

    private static void quickX() {
        double totalTime = 0.0;

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    Integer[] values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    QuickX.sort(values);
                    totalTime += timer.elapsedTime();
                }
            }
            catch (StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, totalTime);
        }
    }

    private static void quickR() {
        double totalTime = 0.0;

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    Integer[] values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    QuickR.sort(values);
                    totalTime += timer.elapsedTime();
                }
            }
            catch (StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, totalTime);
        }
    }

    private static void selection() {
        double totalTime = 0.0;

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    Integer[] values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    Selection.sort(values);
                    totalTime += timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, totalTime);
        }
    }

    private static void insertion() {
        double totalTime = 0.0;

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    Integer[] values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    Insertion.sort(values);
                    totalTime += timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, totalTime);
        }
    }

//    private static String[] genDataStrings(Integer n) {
//        int N = n * THOUSAND;
//        String[] values = new String[N];
//
//        StdRandom.setSeed(SEED);
//        for (int i = 0; i < N; i ++) {
//            Integer x = StdRandom.uniform(RANDON_INT_LBOUND, RANDON_INT_UBOUND);
//            values[i] = x.toString();
//        }
//        return values;
//    }

    private static Integer[] genDataIntegers(Integer n) {
        Integer[] values = new Integer[n];

        switch (TEST_DATA_DIST) {
            case RAND_RANGE:
                StdRandom.setSeed(SEED);
                for (int i = 0; i < n; i++) {
                    Integer x = StdRandom.uniform(RANDON_INT_LBOUND, RANDON_INT_UBOUND);
                    values[i] = x;
                }
                break;
            case IN_ORDER:
                for (int i = 0; i < n; i++) {
                    values[i] = i;
                }
                break;
            case REV_ORDER:
                for (int i = 0; i < n; i++) {
                    values[i] = n - i;
                }
                break;
            case NEARLY_SORTED:
                StdRandom.setSeed(SEED);
                for (int i = 0; i < n; i++) {
                    Integer x = i - StdRandom.uniform(NEARLY_LBOUND, NEARLY_UBOUND);
                    values[i] = x;
                }
                break;
            case NEARLY_SORTED_REV:
                StdRandom.setSeed(SEED);
                for (int i = 0; i < n; i++) {
                    Integer x = n - i - StdRandom.uniform(NEARLY_LBOUND, NEARLY_UBOUND);
                    values[i] = x;
                }
                break;
        }
        if (SHOW_DATA) {
            for (Integer a : values) {
                StdOut.printf("%d\n", a);
            }
        }
        return values;
    }
}

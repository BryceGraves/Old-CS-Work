import java.sql.Array;

public class RunTests {
    enum testDataDist {
      RAND_RANGE
        , IN_ORDER      // When using this, the Quick and QuickX can fault on recursion over 64k elements
        , REV_ORDER     // When using this, the QuickNS and Quick3 can fault on recursion over 8k elements
        , NEARLY_SORTED
        , NEARLY_SORTED_REV
    };
    private static final testDataDist TEST_DATA_DIST = testDataDist.REV_ORDER;
    private static final int TEST_ITERATIONS = 1;
    private static final int THOUSAND = 1000;

    private static final int TEST_LBOUND = 16; // 128K
    //private static final int TEST_LBOUND = 16 * THOUSAND;

    //private static final int TEST_UBOUND = 67000; // ~64 million
    //private static final int TEST_UBOUND = 8192 * 2;
    private static final int TEST_UBOUND = 66 * THOUSAND;
    //private static final int TEST_UBOUND = 17 * THOUSAND * THOUSAND;

    private static final int NEARLY_LBOUND = 0;
    private static final int NEARLY_UBOUND = 10;

    private static final String FORMAT = "%-11d\t%-10s\t%10.4f\t%d\n";
    private static final int SEED = 442;
//    private static final int RANDON_INT_LBOUND = -100 * THOUSAND * THOUSAND;
//    private static final int RANDON_INT_UBOUND = (100 * THOUSAND * THOUSAND) + 1;
    private static final int RANDON_INT_LBOUND = 1;
    private static final int RANDON_INT_UBOUND = (1000000000) + 1;
    private static final boolean SHOW_DATA = false;

    public static void main(String[] args) {

        StdOut.printf("Data set: %s  test iterations %d\n", TEST_DATA_DIST.toString(), TEST_ITERATIONS);

        if (SHOW_DATA) {
            Integer[] values = genDataIntegers(100);

            return;
        }

        selection();
        insertion();
        shell();

        merge();
        mergeBU();
        mergeX();
        quick(true);
        quick(false);
        quickX(true);
        quickX(false);
        quick3(true);
        quick3(false);
        quickBM();

        heap();
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
            StdOut.printf(FORMAT, n, "Selection", totalTime, TEST_ITERATIONS);
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
            StdOut.printf(FORMAT, n, "Insertion", totalTime, TEST_ITERATIONS);
        }
    }

    private static void shell() {
        double totalTime = 0.0;

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    Integer[] values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    Shell.sort(values);
                    totalTime += timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, "Shell", totalTime, TEST_ITERATIONS);
        }
    }

    private static void merge() {
        double totalTime = 0.0;

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    Integer[] values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    Merge.sort(values);
                    totalTime += timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, "Merge", totalTime, TEST_ITERATIONS);
        }
    }

    private static void mergeX() {
        double totalTime = 0.0;

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    Integer[] values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    MergeX.sort(values);
                    totalTime += timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, "MergeX", totalTime, TEST_ITERATIONS);
        }
    }

    private static void mergeBU() {
        double totalTime = 0.0;

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    Integer[] values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    MergeBU.sort(values);
                    totalTime += timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, "MergeBU", totalTime, TEST_ITERATIONS);
        }
    }

    private static void quick(boolean shuffle) {
        double totalTime = 0.0;
        String sort = (shuffle ? "Quick" : "QuickNS");

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    Integer[] values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    Quick.sort(values, shuffle);
                    totalTime += timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, sort, totalTime, TEST_ITERATIONS);
        }
    }

    private static void quickX(boolean shuffle) {
        double totalTime = 0.0;
        String sort = (shuffle ? "QuickX" : "QuickXNS");

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
            catch (java.lang.StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, sort, totalTime, TEST_ITERATIONS);
        }
    }

    private static void quick3(boolean shuffle) {
        double totalTime = 0.0;
        String sort = (shuffle ? "Quick3" : "Quick3NS");

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    Integer[] values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    Quick3way.sort(values, shuffle);
                    totalTime += timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, sort, totalTime, TEST_ITERATIONS);
        }
    }

    private static void quickBM() {
        double totalTime = 0.0;
        String sort = "QuickBM";

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    Integer[] values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    QuickBentleyMcIlroy.sort(values);
                    totalTime += timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, sort, totalTime, TEST_ITERATIONS);
        }
    }

    private static void heap() {
        double totalTime = 0.0;
        String sort = "Heap";

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    Integer[] values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    Heap.sort(values);
                    totalTime += timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, sort, totalTime, TEST_ITERATIONS);
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

public class two_two_seventeen {
    enum testDataDist {
        RAND_RANGE
        , IN_ORDER      // When using this, the Quick and QuickX can fault on recursion over 64k elements
        , REV_ORDER     // When using this, the QuickNS and Quick3 can fault on recursion over 8k elements
        , NEARLY_SORTED
        , NEARLY_SORTED_REV
    };
    private static final testDataDist TEST_DATA_DIST = testDataDist.RAND_RANGE;
    private static final int TEST_ITERATIONS = 1;
    private static final int THOUSAND = 1000;

    private static final int TEST_LBOUND = 16;

    // private static final int TEST_UBOUND = 16;
    private static final int TEST_UBOUND = 9 * THOUSAND * THOUSAND;

    private static final int NEARLY_LBOUND = 0;
    private static final int NEARLY_UBOUND = 10;

    private static final String FORMAT = "%-11d\t%10.4f\n";
    private static final int SEED = 1796402238;
    //    private static final int RANDON_INT_LBOUND = -100 * THOUSAND * THOUSAND;
    //    private static final int RANDON_INT_UBOUND = (100 * THOUSAND * THOUSAND) + 1;
    private static final int RANDON_INT_LBOUND = 0;
    private static final int RANDON_INT_UBOUND = 1000;
    private static final boolean SHOW_DATA = false;

    public static void main(String[] args) {

        StdOut.printf("Data set: %s  test iterations %d\n", TEST_DATA_DIST.toString(), TEST_ITERATIONS);

        if (SHOW_DATA) {
            // Integer[] values = genDataIntegers(100);
            LinkedList values = genLinkedDataIntegers(16);

            return;
        }

        linkedListMergeSort();
        arrayMergeSort();
    }

    private static void linkedListMergeSort() {
        double totalTime = 0.0;

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    LinkedList values = genLinkedDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    values.mergeSort(values.head);
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

    private static void arrayMergeSort() {
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
            catch (StackOverflowError e) {
                totalTime = -1.0;
            }
            catch (Exception e) {
                totalTime = -1.0;
            }
            StdOut.printf(FORMAT, n, totalTime);
        }
    }

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

    private static LinkedList genLinkedDataIntegers(Integer n) {
        LinkedList values = new LinkedList();

        switch (TEST_DATA_DIST) {
            case RAND_RANGE:
                StdRandom.setSeed(SEED);
                for (int i = 0; i < n; i++) {
                    Integer x = StdRandom.uniform(RANDON_INT_LBOUND, RANDON_INT_UBOUND);
                    values.push(x);
                }
                break;
            case IN_ORDER:
                for (int i = 0; i < n; i++) {
                    values.push(i);
                }
                break;
            case REV_ORDER:
                for (int i = 0; i < n; i++) {
                    values.push(n-i);
                }
                break;
            case NEARLY_SORTED:
                StdRandom.setSeed(SEED);
                for (int i = 0; i < n; i++) {
                    Integer x = i - StdRandom.uniform(NEARLY_LBOUND, NEARLY_UBOUND);
                    values.push(x);
                }
                break;
            case NEARLY_SORTED_REV:
                StdRandom.setSeed(SEED);
                for (int i = 0; i < n; i++) {
                    Integer x = n - i - StdRandom.uniform(NEARLY_LBOUND, NEARLY_UBOUND);
                    values.push(x);
                }
                break;
        }
        if (SHOW_DATA) {
            LinkedList.printList(values.mergeSort(values.head));
        }
        return values;
    }
}

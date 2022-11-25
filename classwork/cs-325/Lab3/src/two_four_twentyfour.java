public class two_four_twentyfour extends TriplyLinkedList{
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

    //private static final int TEST_LBOUND = 16; // 128K
    private static final int TEST_LBOUND = 8388608;

    //private static final int TEST_UBOUND = 67000; // ~64 million
    //private static final int TEST_UBOUND = 8192 * 2;
    private static final int TEST_UBOUND = 33554432;

    private static final int NEARLY_LBOUND = 0;
    private static final int NEARLY_UBOUND = 10;

    private static final String FORMAT = "%-11d\t%10.4f\n";
    private static final int SEED = 1796402239;
    //    private static final int RANDON_INT_LBOUND = -100 * THOUSAND * THOUSAND;
    //    private static final int RANDON_INT_UBOUND = (100 * THOUSAND * THOUSAND) + 1;
    private static final int RANDON_INT_LBOUND = 0;
    private static final int RANDON_INT_UBOUND = 200;
    private static final boolean SHOW_DATA = false;

    public static void main(String[] args) {


        TriplyLinkedList values = new TriplyLinkedList();

        values.insert(3);
        values.insert(2);
        values.insert(7);
        values.min();
        values.remove(values.root);
        values.min();
        values.remove(values.root);
        values.min();
        values.remove(values.root);



        StdOut.printf("Data set: %s  test iterations %d\n", TEST_DATA_DIST.toString(), TEST_ITERATIONS);

//        if (SHOW_DATA) {
//            // Integer[] values = genDataIntegers(100);
//            TriplyLinkedList values = genLinkedDataIntegers(7);
//            return;
//        }
        heap();
        linkedListHeap();
    }

    private static void heap() {
        double totalTime = 0.0;

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    MaxPQ<Integer> values = genDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    for (int j = 0; j < values.size() / 2; j++) {
                        values.delMax();
                    }
                    for (int j = 0; j < values.size() / 2; j++) {
                        values.insert(j);
                    }
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

    private static void linkedListHeap() {
        double totalTime = 0.0;

        for (Integer n = TEST_LBOUND; n <= TEST_UBOUND; n *= 2) {
            totalTime = 0.0;

            try {
                for (int i = 0; i < TEST_ITERATIONS; i++) {
                    TriplyLinkedList values = genLinkedDataIntegers(n);
                    Stopwatch timer = new Stopwatch();
                    for (int j = 0; j < values.size() / 2; j++) {
                        values.remove(values.root);
                    }
                    for (int j = 0; j < values.size() / 2; j++) {
                        values.insert(j);
                    }
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

    private static MaxPQ<Integer> genDataIntegers(Integer n) {
        MaxPQ<Integer> values = new MaxPQ<>();

        switch (TEST_DATA_DIST) {
            case RAND_RANGE:
                StdRandom.setSeed(SEED);
                for (int i = 0; i < n; i++) {
                    Integer x = StdRandom.uniform(RANDON_INT_LBOUND, RANDON_INT_UBOUND);
                    values.insert(x);
                }
                break;
            case IN_ORDER:
                for (int i = 0; i < n; i++) {
                    values.insert(i);;
                }
                break;
            case REV_ORDER:
                for (int i = 0; i < n; i++) {
                    values.insert(n - 1);;
                }
                break;
            case NEARLY_SORTED:
                StdRandom.setSeed(SEED);
                for (int i = 0; i < n; i++) {
                    Integer x = i - StdRandom.uniform(NEARLY_LBOUND, NEARLY_UBOUND);
                    values.insert(x);;
                }
                break;
            case NEARLY_SORTED_REV:
                StdRandom.setSeed(SEED);
                for (int i = 0; i < n; i++) {
                    Integer x = n - i - StdRandom.uniform(NEARLY_LBOUND, NEARLY_UBOUND);
                    values.insert(x);
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

    private static TriplyLinkedList genLinkedDataIntegers(Integer n) {
        TriplyLinkedList values = new TriplyLinkedList();

        switch (TEST_DATA_DIST) {
            case RAND_RANGE:
                StdRandom.setSeed(SEED);
                for (int i = 0; i < n; i++) {
                    Integer x = StdRandom.uniform(RANDON_INT_LBOUND, RANDON_INT_UBOUND);
                    values.insert(x);
                }
                break;
            case IN_ORDER:
                for (int i = 0; i < n; i++) {
                    values.insert(i);
                }
                break;
            case REV_ORDER:
                for (int i = 0; i < n; i++) {
                    values.insert(n - i);
                }
                break;
            case NEARLY_SORTED:
                StdRandom.setSeed(SEED);
                for (int i = 0; i < n; i++) {
                    Integer x = i - StdRandom.uniform(NEARLY_LBOUND, NEARLY_UBOUND);
                    values.insert(x);
                }
                break;
            case NEARLY_SORTED_REV:
                StdRandom.setSeed(SEED);
                for (int i = 0; i < n; i++) {
                    Integer x = n - i - StdRandom.uniform(NEARLY_LBOUND, NEARLY_UBOUND);
                    values.insert(x);
                }
                break;
        }
        if (SHOW_DATA) {
            StdOut.println(values.size());
            values.printList();
            values.min();
            values.remove(values.root);
            values.min();
            values.printList();
            values.min();
            values.remove(values.root);
            values.min();
            values.printList();
            values.min();
            values.remove(values.root);
            values.min();
            values.printList();
            StdOut.println(values.size());
        }
        return values;
    }
}

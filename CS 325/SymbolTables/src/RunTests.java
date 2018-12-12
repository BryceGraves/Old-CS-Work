public class RunTests {
    enum testDataDist {
        RAND_RANGE
        , IN_ORDER      // When using this, the Quick and QuickX can fault on recursion over 64k elements
        , REV_ORDER
    };
    private static final testDataDist TEST_DATA_DIST = testDataDist.RAND_RANGE;
    private static final int TEST_ITERATIONS = 1;
    private static final int THOUSAND = 1000;

    private static final int TEST_LBOUND = 2 * THOUSAND;
    private static final int TEST_UBOUND = 10 * THOUSAND * THOUSAND;
    //private static final int TEST_UBOUND = 10 * THOUSAND * THOUSAND;

    private static final int SEED = 442;
    private static final int RANDOM_INT_LBOUND = 1;
    private static final int RANDOM_INT_UBOUND = (100000000) + 1;
    private static final String FORMAT = "%-18s\t%10d\t%10.4f\t%10.4f\t%10.4f\t%10.4f\t%10.4f\t\t%d\t%d\n";

    public static void main(String[] args) {
        StdOut.printf("Data set: %s  test iterations %d\n", TEST_DATA_DIST.toString(), TEST_ITERATIONS);
        StdOut.printf("ST\t\t\t\t\t\t\tN\t\tput\t\t\tget\t\t\tmax\t\t\tcieling\t\tdelete\n");

        // sequentialSearchST();
        // binarySearchST();
        bst();
        redBlackBST();
    }

    private static void sequentialSearchST() {
        double putTime, getTime, maxTime, cielTime, deleteTime;
        for (int loop = TEST_LBOUND; loop < TEST_UBOUND; loop *= 2)
        {
            StdRandom.setSeed(SEED);
            int i = -1;
            SequentialSearchST<String, Integer> st = new SequentialSearchST<String, Integer>();

            try {
                Stopwatch timer = new Stopwatch();
                for (i = 0; i < loop; i++) {
                    String key = genDataString(i);
                    st.put(key, i);
                }
                putTime = timer.elapsedTime();

                timer = new Stopwatch();
                for (String s : st.keys()) {
                    //StdOut.println(s + " " + st.get(s));
                    st.get(s);
                }
                getTime = timer.elapsedTime();

                timer = new Stopwatch();
//                for (int j = 0; j < 100000; j++) {
//                    String max = st.max();
//                }
//                maxTime = timer.elapsedTime();
                maxTime = -42;

                        timer = new Stopwatch();
//                for (String s : st.keys()) {
//                    st.ceiling(s);
//                }
//                cielTime = timer.elapsedTime();
                cielTime = -42;

                {
                    // delete chunk of code
                    timer = new Stopwatch();
                    int j = 0;
                    for (String s : st.keys()) {
                        st.delete(s);
                        j++;
                        if (j > loop / 2)
                            break;
                    }
                    for (j = 0; j < loop / 2; j++) {
                        String key = genDataString(j);
                        st.put(key, j);
                    }
                    for (String s : st.keys()) {
                        st.delete(s);
                        j++;
                        if (j > loop / 2)
                            break;
                    }
                    for (j = 0; j < loop / 2; j++) {
                        String key = genDataString(j);
                        st.put(key, j);
                    }
                    for (String s : st.keys()) {
                        st.delete(s);
                    }
                    deleteTime = timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                putTime = getTime = maxTime = cielTime = deleteTime = -1.0;
            }
            catch (Exception e) {
                putTime = getTime = maxTime = cielTime = deleteTime = -2.0;
            }

            StdOut.printf(FORMAT, "SequentialSearchST", loop, putTime, getTime, maxTime, cielTime, deleteTime, -1, -1);
        }
    }

    private static void binarySearchST() {
        double putTime, getTime, maxTime, cielTime, deleteTime;
        for (int loop = TEST_LBOUND; loop < TEST_UBOUND; loop *= 2)
        {
            StdRandom.setSeed(SEED);
            int i = -1;
            BinarySearchST<String, Integer> st = new BinarySearchST<String, Integer>();

            try {
                Stopwatch timer = new Stopwatch();
                for (i = 0; i < loop; i++) {
                    String key = genDataString(i);
                    st.put(key, i);
                }
                putTime = timer.elapsedTime();

                timer = new Stopwatch();
                for (String s : st.keys()) {
                    //StdOut.println(s + " " + st.get(s));
                    st.get(s);
                }
                getTime = timer.elapsedTime();

                timer = new Stopwatch();
                for (int j = 0; j < 100000; j++) {
                    String max = st.max();
                }
                maxTime = timer.elapsedTime();

                timer = new Stopwatch();
                for (String s : st.keys()) {
                    st.ceiling(s);
                }
                cielTime = timer.elapsedTime();

                {
                    // delete chunk of code
                    timer = new Stopwatch();
                    int j = 0;
                    for (String s : st.keys()) {
                        st.delete(s);
                        j++;
                        if (j > loop / 2)
                            break;
                    }
                    for (j = 0; j < loop / 2; j++) {
                        String key = genDataString(j);
                        st.put(key, j);
                    }
                    for (String s : st.keys()) {
                        st.delete(s);
                        j++;
                        if (j > loop / 2)
                            break;
                    }
                    for (j = 0; j < loop / 2; j++) {
                        String key = genDataString(j);
                        st.put(key, j);
                    }
                    for (String s : st.keys()) {
                        st.delete(s);
                    }
                    deleteTime = timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                putTime = getTime = maxTime = cielTime = deleteTime = -1.0;
            }
            catch (Exception e) {
                putTime = getTime = maxTime = cielTime = deleteTime = -2.0;
            }

            StdOut.printf(FORMAT, "BinarySearchST", loop, putTime, getTime, maxTime, cielTime, deleteTime, -1, -1);
        }
    }

    private static void bst() {
        double putTime, getTime, maxTime, cielTime, deleteTime;
        int height1 = -1;
        int height2 = -1;
        for (int loop = TEST_LBOUND; loop < TEST_UBOUND; loop *= 2)
        {
            height1 = -1;
            height2 = -1;
            StdRandom.setSeed(SEED);
            int i = -1;
            BST<String, Integer> st = new BST<String, Integer>();

            try {
                Stopwatch timer = new Stopwatch();
                for (i = 0; i < loop; i++) {
                    String key = genDataString(i);
                    st.put(key, i);
                }
                putTime = timer.elapsedTime();

                timer = new Stopwatch();
                for (String s : st.keys()) {
                    //StdOut.println(s + " " + st.get(s));
                    st.get(s);
                }
                getTime = timer.elapsedTime();

                timer = new Stopwatch();
                for (int j = 0; j < 100000; j++) {
                    String max = st.max();
                }
                maxTime = timer.elapsedTime();

                timer = new Stopwatch();
                for (String s : st.keys()) {
                    st.ceiling(s);
                }
                cielTime = timer.elapsedTime();
                height1 = st.height();

                {
                    // delete chunk of code
                    timer = new Stopwatch();
                    int j = 0;
                    for (String s : st.keys()) {
                        st.delete(s);
                        j++;
                        if (j > loop / 2)
                            break;
                    }
                    for (j = 0; j < loop / 2; j++) {
                        String key = genDataString(j);
                        st.put(key, j);
                    }
                    for (String s : st.keys()) {
                        st.delete(s);
                        j++;
                        if (j > loop / 2)
                            break;
                    }
                    for (j = 0; j < loop / 2; j++) {
                        String key = genDataString(j);
                        st.put(key, j);
                    }
                    height2 = st.height();
                    for (String s : st.keys()) {
                        st.delete(s);
                    }
                    deleteTime = timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                putTime = getTime = maxTime = cielTime = deleteTime = -1.0;
            }
            catch (Exception e) {
                putTime = getTime = maxTime = cielTime = deleteTime = -2.0;
            }

            StdOut.printf(FORMAT, "BST", loop, putTime, getTime, maxTime, cielTime, deleteTime, height1, height2);
        }
    }

    private static void redBlackBST() {
        double putTime, getTime, maxTime, cielTime, deleteTime;
        int height1 = -1;
        int height2 = -1;
        for (int loop = TEST_LBOUND; loop < TEST_UBOUND; loop *= 2)
        {
            height1 = -1;
            height2 = -1;
            StdRandom.setSeed(SEED);
            int i = -1;
            RedBlackBST<String, Integer> st = new RedBlackBST<String, Integer>();

            try {
                Stopwatch timer = new Stopwatch();
                for (i = 0; i < loop; i++) {
                    String key = genDataString(i);
                    st.put(key, i);
                }
                putTime = timer.elapsedTime();

                timer = new Stopwatch();
                for (String s : st.keys()) {
                    //StdOut.println(s + " " + st.get(s));
                    st.get(s);
                }
                getTime = timer.elapsedTime();

                timer = new Stopwatch();
                for (int j = 0; j < 100000; j++) {
                    String max = st.max();
                }
                maxTime = timer.elapsedTime();

                timer = new Stopwatch();
                for (String s : st.keys()) {
                    st.ceiling(s);
                }
                cielTime = timer.elapsedTime();
                height1 = st.height();

                {
                    // delete chunk of code
                    timer = new Stopwatch();
                    int j = 0;
                    for (String s : st.keys()) {
                        st.delete(s);
                        j++;
                        if (j > loop / 2)
                            break;
                    }
                    for (j = 0; j < loop / 2; j++) {
                        String key = genDataString(j);
                        st.put(key, j);
                    }
                    for (String s : st.keys()) {
                        st.delete(s);
                        j++;
                        if (j > loop / 2)
                            break;
                    }
                    for (j = 0; j < loop / 2; j++) {
                        String key = genDataString(j);
                        st.put(key, j);
                    }
                    height2 = st.height();
                    for (String s : st.keys()) {
                        st.delete(s);
                    }
                    deleteTime = timer.elapsedTime();
                }
            }
            catch (java.lang.StackOverflowError e) {
                putTime = getTime = maxTime = cielTime = deleteTime = -1.0;
            }
            catch (Exception e) {
                putTime = getTime = maxTime = cielTime = deleteTime = -2.0;
            }

            StdOut.printf(FORMAT, "RedBlackBST", loop, putTime, getTime, maxTime, cielTime, deleteTime, height1, height2);
        }
    }

    private static String genDataString(int i) {
        Integer x = 0;

        switch (TEST_DATA_DIST) {
            case RAND_RANGE:
                x = StdRandom.uniform(RANDOM_INT_LBOUND, RANDOM_INT_UBOUND);
            case IN_ORDER:
                x = i;
                break;
            case REV_ORDER:
                x = RANDOM_INT_UBOUND - i;
                break;
        };
        return x.toString();
    }
}

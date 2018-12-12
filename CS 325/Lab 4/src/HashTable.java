public class HashTable<Key extends Comparable, Value> {
    private static final int INIT_CAPACITY = 5;
    private static final int RESIZE_UP_FACTOR = 70;
    private static final int RESIZE_DOWN_FACTOR = 25;
    private static final int RESIZE_DOWN_THRESHOLD = 11;
    private boolean isResizeAble = false;

    // The number of keys in the hash table
    private int n;

    // the number of slots in the hash table
    private int m;

    // And, the actual hash table
    private Node[] st;

    // Next time, just use the LinkedList class.
    private class Node<Key extends Comparable, Value> {
        private Key key;
        private Value val;
        private Node next;

        private Node(){ }

        public Node(Key k, Value v) {
            key = k;
            val = v;
            next = null;
        }
    }

    // not tested
    public HashTable() {
        this(INIT_CAPACITY);
    }

    public HashTable(int m) {
        if (m <= 0) {
            throw new IllegalArgumentException("HashTable: initial size must be > 0");
        }
        this.m = m;
        //st = new Node[m];
        st = (Node<Key, Value>[]) new Node[m];
        for (int i = 0; i < m; i++) {
            st[i] = null;
        }
    }

    public HashTable(int m, boolean autoResize) {
        this(m);
        isResizeAble = autoResize;
    }

    private int hash(Key key) {
        return (key.hashCode() & 0x7fffffff) % m;
    }

    public int size() {
        return n;
    }

    public int hsize() {
        return m;
    }

    public void ResizeableT() {
        isResizeAble = true;
    }

    public void ResizeableF() {
        isResizeAble = false;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public void put(Key key, Value val) {
        if (key == null) {
            throw new IllegalArgumentException("put: called with null key");
        }
        if (val == null) {
            //throw new IllegalArgumentException("put: null value");
            delete(key);
        }
        else {
            int i = hash(key);
            if (st[i] == null) {
                st[i] = new Node(key, val);
                n++;
                if (isResizeAble) {
                    resize();
                }
            }
            else {
                for (Node node = st[i]; node != null; node = node.next) {
                    if (key.equals(node.key)) {
                        node.val = val;
                        break;
                    }
                    if (node.next == null) {
                        node.next = new Node(key, val);
                        n++;
                        if (isResizeAble)
                            resize();
                    }
                }
                // you might think you want to do the following.
                // Wrong! This would not allow replacements.
                //            Node nn = new Node(key, val);
                //            nn.next = st[i];
                //            st[i] = nn;
            }
        }
    }

    public Value get(Key key) {
        if (key == null) {
            throw new IllegalArgumentException("get: called with null key");
        }
        int i = hash(key);
        Value retVal = null;

        for (Node node = st[i]; node != null; node = node.next) {
            if (key.equals(node.key)) {
                retVal = (Value) node.val;
            }
        }
        return retVal;
    }

    public boolean contains(Key key) {
        if (key == null) {
            throw new IllegalArgumentException("contains: called with null key");
        }
        return get(key) != null;
    }

    public void show() {
        for (int i = 0; i < m; i++) {
            for (Node node = st[i]; node != null; node = node.next) {
                System.out.println("Key: " + node.key + "   Value: " + node.val);
            }
        }
    }

    public int maxLen() {
        int retVal = 0;

        for (int i = 0, curMax = 0; i < m; i++) {
            curMax = 0;
            for (Node node = st[i]; node != null; node = node.next) {
                curMax++;
            }
            if (curMax > retVal) {
                retVal = curMax;
            }
        }

        return retVal;
    }

    // resize up when n / m >= 8
    // resize down when n / m <= 2 && m > 10
    // resize the hash table to have the given number of chains,
    // rehashing all of the keys
    private void resize() {
        // Understand me.
        if (isResizeAble) {
            int resizeFactor = (int) (((float) n) / ((float) m) * 100.0f);
            int newSize = 0;

            if (resizeFactor > RESIZE_UP_FACTOR) {
                newSize = m * 2;
            } else if (resizeFactor < RESIZE_DOWN_FACTOR && m > RESIZE_DOWN_THRESHOLD) {
                newSize = m / 2;
            }
            if (newSize != 0) {
                System.out.println("*** resizing from " + m + " to " + newSize + " ***");
                HashTable<Key, Value> temp = new HashTable<Key, Value>(newSize);

                for (int i = 0; i < m; i++) {
                    for (Node node = st[i]; node != null; node = node.next) {
                        temp.put((Key) node.key, (Value) node.val);
                    }
                }
                this.m = temp.m;
                this.n = temp.n;
                this.st = temp.st;
            }
        }
    }

    public void delete(Key key) {
        if (key == null) throw new IllegalArgumentException("You need to give me a key bro");
        int hashOfKey = hash(key);
        st[hashOfKey] = delete(st[hashOfKey], key);
        resize();
    }

    private Node delete(Node current, Key key)  {
        if (current == null) return null;
        if (key.equals(current.key)) {
            n--;
            return current.next;
        }
        current.next = delete(current.next, key);
        return current;
    }

    public static void main(String[] args) {
        {
            HashTable<Integer, Integer> st = new HashTable<>(5, true);

            for (int i = 0; i < 100; i++) {
                st.put(i, i);
                assert st.contains(i);
            }
            assert st.size() == 100;
            assert st.hsize() == st.m;
            assert st.m > 5;
            for (int i = 0; i < 80; i++) {
                st.delete(i);
                assert !st.contains(i);
            }
            assert st.size() == 20;
            assert st.hsize() == st.m;
            assert st.m < 100;
            int om = st.m;
            for (int i = 0; i < 20; i++) {
                st.put(i, i);
                assert st.contains(i);
            }
            assert st.size() == 40;
            assert st.hsize() == st.m;
            assert st.m < 100;
            assert om == st.m;
            for (int i = 20; i < 40; i++) {
                st.put(i, i);
                assert st.contains(i);
            }
            assert st.size() == 60;
            assert st.hsize() == st.m;
            assert st.m > 100;

            om = st.m;
            st.ResizeableF();
            for (int i = 0; i < 90; i++) {
                st.delete(i);
                assert !st.contains(i);
            }
            assert om == st.m;
        }
        String[] numNames = {
                "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve"
        };
        {
            HashTable<String, Integer> st = new HashTable<String, Integer>(5);

            st.ResizeableT();
            for (int i = 0; i < numNames.length; i++) {
                st.put(numNames[i], i);
            }

            System.out.println("Empty: " + st.isEmpty());
            System.out.println("Size : " + st.size());
            System.out.println("HSize: " + st.hsize());
            System.out.println("---------------------------");
            st.show();
            System.out.println("---------------------------");
            System.out.println("Contains One: " + st.contains("One"));
            System.out.println("Contains Twenty: " + st.contains("Twenty"));

            System.out.println("---------------------------");
            System.out.println("Max List Len: " + st.maxLen());

            for (int i = numNames.length - 1; i >= 0; i--) {
                st.delete(numNames[i]);
            }
        }
    }
}

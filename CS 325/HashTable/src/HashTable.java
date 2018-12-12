//TODO: Rename and comment on things

public class HashTable <Key extends Comparable<Key>, Value> {
    private static final int INT_CAP = 5;

    private int n;
    private int m;

    private Node[] st;

    private class Node<Key extends Comparable<Key>, Value> {
        private Key key;
        private Value value;
        private Node nextValue;

        private Node() {};

        public Node(Key key, Value value) {
            this.key = key;
            this.value = value;
            this.nextValue = null;
        }
    }

    public HashTable() { this(INT_CAP); }

    public HashTable(int hash) {
        this.m = hash;
        st = new Node[m];

        for (int i = 0; i < m; i++) {
            st[i] = null;
        }
    }

    private int hash(Key key) { return (key.hashCode() & 0x7fffffff) % m; }

    public int size() { return n; }

    public int hsize() { return m; }

    public boolean isEmpty() { return size() == 0; }

    public boolean contains(Key key) {
        if (key == null) { throw new IllegalArgumentException("Give me a key!"); }
        return get(key) != null;
    }


    public void put(Key key, Value value) {
        if (key == null) {
            throw new IllegalArgumentException();
        }
        if (value == null) {
            throw new IllegalArgumentException();
        }

        if ((n / m) >= 8) {
            resize();
        }

        int i = hash(key);

        if (st[i] == null) {
            st[i] = new Node(key, value);
            n++;
        } else {
            for (Node node = st[i]; node != null; node = node.nextValue) {
                if (key.equals(node.key)) {
                    node.value = value;
                    break;
                }

                if (node.nextValue == null) {
                    node.nextValue = new Node(key, value);
                    n++;
                }
            }
        }
    }

    public Value get(Key key) {
        if (key == null) {
            throw new IllegalArgumentException();
        }

        int i = hash(key);
        Value returnValue = null;

        for (Node node = st[i]; node != null; node = node.nextValue) {
            if (key.equals(node.key)) {
                returnValue = (Value) node.value;
                break;
            }
        }

        return returnValue;
    }

    public void show() {
        int iteration = 1;
        for (int i = 0; i < m; i++) {
            for (Node node = st[i]; node != null; node = node.nextValue) {
                System.out.println("Key: " + node.key + "  Value: " + node.value);
                System.out.println(iteration++);
            }
        }
    }

    public void resize() {
        HashTable<Key, Value> tempTable = new HashTable<>(m * 2);
        for (int i = 0; i < m; i++) {
            for (Node node = st[i]; node != null; node = node.nextValue) {
                tempTable.put((Key) node.key, (Value) node.value);
            }
        }
        this.n = tempTable.n;
        this.m = tempTable.m;
        this.st = tempTable.st;
    }

    public void delete(Key key) {
        if (key == null) throw new IllegalArgumentException("You need to give me a key bro");
        int hashOfKey = hash(key);
        if (!contains(key)) throw new IllegalArgumentException("We don't have that key bro");

        for (Node node = st[hashOfKey]; node.nextValue != null; node = node.nextValue) {
            if (key.equals(node.key)) {
                st[hashOfKey] = node.nextValue;
                n--;
                return;
            } else if (key.equals(node.nextValue.key)) {
                Node temp = node.nextValue.nextValue;
                node.nextValue = temp;
                n--;
                return;
            }
        }
    }

    public static void main(String args[]) {
        {
            HashTable<String, Integer> st = new HashTable<>(2);

            for (Integer i = 0; i < 40; i++) {
                st.put(i.toString(),i);
            }
            st.show();
            System.out.println(st.size());
            System.out.println(st.hsize());
            System.out.println("---------------------------------");

            for (Integer i = 30; i < 40; i++) {
                st.delete(i.toString());
            }

            st.show();
            System.out.println(st.size());
            System.out.println(st.hsize());
            System.out.println("---------------------------------");

            for (Integer i = 0; i < 10; i++) {
                st.delete(i.toString());
            }

            st.show();

            System.out.println(st.size());
            System.out.println(st.hsize());

        }
    }
}

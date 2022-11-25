import java.util.NoSuchElementException;

public class AVL_Tree<Key extends Comparable<Key>, Value>  {
    private Node root;

    private class Node {
        private Key key;
        private Value value;
        private Node left;
        private Node right;
        private int size;
        private int height;

        // you cannot create a Node without a key or value.
        private Node() { key = null; }

        public Node(Key key, Value value) {
            this.key = key;
            this.value = value;
            this.left = this.right = null;
            this.size = this.height = 1;
        }
    }

    public AVL_Tree() { root = null; }

    public boolean isEmpty() { return root == null; }

    public int size() { return size(root); }

    private int size(Node node) { return (node == null ? 0 : node.size); }

    public void put(Key key, Value value) {
        if (key == null) {
            throw new IllegalArgumentException("put: null key not allowed");
        }
        if (value == null) {
            deleteAtLocation(key);
            return;
        }
        else {
            root = put(root, key, value);
        }
    }

    private Node put(Node node, Key key, Value value) {
        // reached the bottom of the tree, create and return a new node.
        if (node == null) {
            node = new Node(key, value);
        } else {
            int compareVal = key.compareTo(node.key);
            if (compareVal < 0) {
                // recursive call
                node.left = put(node.left, key, value);
            } else if (compareVal > 0) {
                // recursive call
                node.right = put(node.right, key, value);
            } else {
                // equal keys, replace
                node.value = value;
            }
            // need to set the size and height
            node.size = 1 + size(node.left) + size(node.right);
            node.height = 1 + Math.max(height(node.left), height(node.right));
        }
        return balance(node);
    }

    private Node balance(Node node) {
        if (balanceFactor(node) < -1) {
            if (balanceFactor(node.right) > 0) {
                node.right = rotateRight(node.right);
            }
            node = rotateLeft(node);
        } else if (balanceFactor(node) > 1) {
            if (balanceFactor(node.left) < 0) {
                node.left = rotateLeft(node.left);
            }
            node = rotateRight(node);
        }
        return node;
    }

    private Node rotateLeft(Node node) {
        // Use current node's right node as pivot
        Node pivot = node.right;

        // Assign current node's right to pivot's left node
        node.right = pivot.left;
        pivot.left = node;
        pivot.size = node.size;

        node.size = 1 + size(node.left) + size(node.right);
        node.height = 1 + Math.max(height(node.left), height(node.right));
        pivot.height = 1 + Math.max(height(pivot.left), height(pivot.right));

        return pivot;
    }

    private Node rotateRight(Node node) {
        // Use current node's left node as pivot
        Node pivot = node.left;

        // Assign current node's right to pivot's left node
        node.left = pivot.right;
        pivot.right = node;

        pivot.size = node.size;
        node.size = 1 + size(node.left) + size(node.right);
        node.height = 1 + Math.max(height(node.left), height(node.right));
        pivot.height = 1 + Math.max(height(pivot.left), height(pivot.right));

        return pivot;
    }

    private int balanceFactor(Node node) { return height(node.left) - height(node.right); }

    public Value get(Key key) { return get(root, key); }

    private Value get(Node node, Key key) {
        Value retValue = null;

        if (key == null) {
            throw new IllegalArgumentException("get: null key not allowed");
        }
        else {
            if (node != null) {
                int compareVal = key.compareTo(node.key);
                if (compareVal < 0) {
                    // recursive call
                    retValue = get(node.left, key);
                } else if (compareVal > 0) {
                    // recursive call
                    retValue = get(node.right, key);
                } else {
                    retValue = node.value;
                }
            }
        }
        return retValue;
    }

    public boolean contains(Key key) {
        return get(key) != null;
    }

    public int height() { return height(root); }

    private int height(Node node) {
        if (node == null) return 0;
        return node.height;
    }

    public void inOrder() { inOrder(root); }

    private void inOrder(Node node) {
        if (node == null) {
            return;
        }
        else {
            if (node.left != null) {
                inOrder(node.left);
            }
            System.out.println("key: " + node.key + "   value: " + node.value);
            if (node.right != null) {
                inOrder(node.right);
            }
        }
    }

    public Key min() { return min(root).key; }

    private Node min(Node node) {
        if (node == null)
            throw new IllegalArgumentException("max: empty tree");
        if (node.left != null)
            return min(node.left);
        else
            return node;
    }

    public Key max() { return max(root).key; }

    private Node max(Node node) {
        if (node == null)
            throw new IllegalArgumentException("max: empty tree");
        if (node.right != null)
            return max(node.right);
        else
            return node;
    }

    private Key root() { return root.key; }

    private double avgHeight() {
        if (root == null) return 0.0;
        double heightSum;

        heightSum = avgHeight(root.left, 1) + avgHeight(root.right, 1);

        return heightSum / root.size;
    }

    private double avgHeight(Node node, int hth) {
        if (node == null) return 0.0;
        return hth + avgHeight(node.left, hth + 1) + avgHeight(node.right, hth + 1);
    }

    public Value deleteAtLocation(Key key) {
        Value toReturn = get(key);
        delete(key);
        return toReturn;
    }

    public void delete(Key key) {
        root = delete(root, key);
    }

    private Node delete(Node current, Key key)
    {
        // Return null if list is empty
        if (current == null)  return current;

        // Assign the compare to return so we don't have to again
        int compareValue = key.compareTo(current.key);

        // We must go deeper
        if (compareValue < 0) {
            current.left = delete(current.left, key);
        } else if (compareValue > 0) {
            current.right = delete(current.right, key);
        } else {

            // Check for children
            if (current.left == null)
                return current.right;
            else if (current.right == null)
                return current.left;

            // Nab and delete the smallest of the right subtree if we end on a node with two children
            current.key = min(current.right).key;
            current.value = min(current.right).value;
            current.right = delete(current.right, current.key);
        }

        current.size = 1 + size(current.left) + size(current.right);
        current.height = 1 + Math.max(height(current.left), height(current.right));
        return balance(current);
    }

    public Value deleteMin() {
        Node minNode = min(root);

        Value toReturn = minNode.value;

        deleteAtLocation(minNode.key);
        return toReturn;
    }


    public Value deleteMax() {
        Node maxNode = max(root);

        Value toReturn = maxNode.value;

        deleteAtLocation(maxNode.key);
        return toReturn;
    }

    public Iterable<Key> keys() { return keysInOrder(); }

    public Iterable<Key> keysInOrder() {
        Queue<Key> queue = new Queue<>();
        keysInOrder(root, queue);
        return queue;
    }

    private void keysInOrder(Node x, Queue<Key> queue) {
        if (x == null) return;
        keysInOrder(x.left, queue);
        queue.enqueue(x.key);
        keysInOrder(x.right, queue);
    }

    public static void main(String[] args) {
        System.out.println("---------------------------");
        {
            AVL_Tree<String, String> avl = new AVL_Tree<>();

            avl.put("C", "C");
            avl.put("B", "B");
            avl.put("A", "A");

            assert avl.size() == 3;
            assert avl.height() == 2;
            assert avl.root.value.equals("B");
            assert avl.root.left.value.equals("A");
            assert avl.root.right.value.equals("C");

            assert avl.get("C").equals("C");
            assert avl.get("B").equals("B");
            assert avl.get("A").equals("A");

            assert avl.contains("C");
            assert avl.contains("B");
            assert avl.contains("A");

            String[] keys = {"A", "B", "C"};
            int i = 0;
            for (String s : avl.keys()) {
                assert keys[i++].equals(s);
            }

            System.out.println("success Left-Left Case");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<String, String> avl = new AVL_Tree<>();

            avl.put("A", "A");
            avl.put("B", "B");
            avl.put("C", "C");

            assert avl.size() == 3;
            assert avl.height() == 2;
            assert avl.root.value.equals("B");
            assert avl.root.left.value.equals("A");
            assert avl.root.right.value.equals("C");

            assert avl.get("C").equals("C");
            assert avl.get("B").equals("B");
            assert avl.get("A").equals("A");

            String[] keys = {"A", "B", "C"};
            int i = 0;
            for (String s : avl.keys()) {
                assert keys[i++].equals(s);
            }

            System.out.println("success Right-Right Case");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<String, String> avl = new AVL_Tree<>();

            avl.put("D", "D");
            avl.put("B", "B");
            avl.put("C", "C");

            assert avl.size() == 3;
            assert avl.height() == 2;
            assert avl.root.value.equals("C");
            assert avl.root.left.value.equals("B");
            assert avl.root.right.value.equals("D");

            assert avl.get("C").equals("C");
            assert avl.get("B").equals("B");
            assert avl.get("D").equals("D");

            String[] keys = {"B", "C", "D"};
            int i = 0;
            for (String s : avl.keys()) {
                assert keys[i++].equals(s);
            }

            System.out.println("success Left-Right Case");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<String, String> avl = new AVL_Tree<>();

            avl.put("A", "A");
            avl.put("C", "C");
            avl.put("B", "B");
            assert avl.root.value.equals("B");
            assert avl.root.left.value.equals("A");
            assert avl.root.right.value.equals("C");

            assert avl.get("C").equals("C");
            assert avl.get("B").equals("B");
            assert avl.get("A").equals("A");

            String[] keys = {"A", "B", "C"};
            int i = 0;
            for (String s : avl.keys()) {
                assert keys[i++].equals(s);
            }

            System.out.println("success Right-Left Case");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<Integer, Integer> avl = new AVL_Tree<>();

            avl.put(12, 12);
            avl.put(8, 8);
            avl.put(18, 18);
            avl.put(5, 5);
            avl.put(11, 11);
            avl.put(10, 10);

            assert avl.size() == 6;
            assert avl.height() == 3;
            assert avl.root.value == 11;
            assert avl.root.left.value == 8;
            assert avl.root.left.right.value == 10;
            assert avl.root.left.left.value == 5;
            assert avl.root.right.value == 12;
            assert avl.root.right.right.value == 18;
            assert avl.root.right.left == null;

            Integer[] keys = {5,8,10,11,12,18};
            int i = 0;
            for (Integer s : avl.keys()) {
                assert keys[i++].equals(s);
            }

            System.out.println("success Right-Left up");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<Integer, Integer> avl = new AVL_Tree<>();

            avl.put(12, 12);
            avl.put(8, 8);
            avl.put(18, 18);
            avl.put(5, 5);
            avl.put(11, 11);
            avl.put(7, 7);
            assert avl.root.value == 8;
            assert avl.root.left.value == 5;
            assert avl.root.left.right.value == 7;
            assert avl.root.left.left == null;
            assert avl.root.right.value == 12;
            assert avl.root.right.right.value == 18;
            assert avl.root.right.left.value == 11;
            System.out.println("success Left-Right up");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<Integer, Integer> avl = new AVL_Tree<>();

            avl.put(12, 12);
            avl.put(8, 8);
            avl.put(18, 18);
            avl.put(5, 5);
            avl.put(11, 11);
            avl.put(17, 17);
            avl.put(15, 15);
            assert avl.root.value == 12;
            assert avl.root.left.value == 8;
            assert avl.root.left.right.value == 11;
            assert avl.root.left.left.value == 5;
            assert avl.root.right.value == 17;
            assert avl.root.right.right.value == 18;
            assert avl.root.right.left.value == 15;
            System.out.println("success Left-Left up2");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<String, String> avl = new AVL_Tree<>();

            avl.put("C", "C");
            assert avl.contains("C");
            avl.deleteMin();
            assert !avl.contains("C");
            assert avl.root == null;
            System.out.println("success deleteMin 1 node");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<String, String> avl = new AVL_Tree<>();

            avl.put("C", "C");
            assert avl.contains("C");
            avl.deleteMax();
            assert !avl.contains("C");
            assert avl.root == null;
            System.out.println("success deleteMax 1 node");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<String, String> avl = new AVL_Tree<>();

            avl.put("C", "C");
            assert avl.contains("C");
            avl.delete("C");
            assert !avl.contains("C");
            assert avl.root == null;
            System.out.println("success delete 1 node");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<String, String> avl = new AVL_Tree<>();

            avl.put("A", "A");
            avl.put("C", "C");
            avl.put("B", "B");
            String min = avl.min();
            assert min.equals("A");
            assert avl.contains("A");
            avl.deleteMin();
            assert !avl.contains("A");
            assert avl.root.value.equals("B");
            assert avl.root.left == null;
            assert avl.root.right.value.equals("C");
            System.out.println("success deleteMin");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<String, String> avl = new AVL_Tree<>();

            avl.put("A", "A");
            avl.put("C", "C");
            avl.put("B", "B");
            String max = avl.max();
            assert max.equals("C");
            assert avl.contains("C");
            avl.deleteMax();
            assert !avl.contains("C");
            assert avl.root.value.equals("B");
            assert avl.root.left.value.equals("A");
            assert avl.root.right == null;
            System.out.println("success deleteMax");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<Integer, Integer> avl = new AVL_Tree<>();

            avl.put(12, 12);
            avl.put(8, 8);
            avl.put(18, 18);
            avl.put(5, 5);
            avl.put(11, 11);
            avl.put(17, 17);
            avl.put(4, 4);
            Integer max = avl.max();
            assert max == 18;
            assert avl.contains(18);
            avl.deleteMax();
            assert !avl.contains(18);
            assert avl.root.value == 8;
            assert avl.root.left.value == 5;
            assert avl.root.left.right == null;
            assert avl.root.left.left.value == 4;
            assert avl.root.right.value == 12;
            assert avl.root.right.right.value == 17;
            assert avl.root.right.left.value == 11;
            System.out.println("success deleteMax");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<Integer, Integer> avl = new AVL_Tree<>();

            avl.put(8, 8);
            avl.put(5, 5);
            avl.put(12, 12);
            avl.put(4, 4);
            avl.put(11, 11);
            avl.put(18, 18);
            avl.put(17, 17);
            Integer min = avl.min();
            assert min == 4;
            assert avl.contains(4);
            avl.deleteMin();
            assert !avl.contains(4);
            assert avl.root.value == 12;
            assert avl.root.left.value == 8;
            assert avl.root.left.right.value == 11;
            assert avl.root.left.left.value == 5;
            assert avl.root.right.value == 18;
            assert avl.root.right.right == null;
            assert avl.root.right.left.value == 17;
            System.out.println("success deleteMin");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<Integer, Integer> avl = new AVL_Tree<>();

            avl.put(12, 12);
            avl.put(8, 8);
            avl.put(18, 18);
            avl.put(5, 5);
            avl.put(11, 11);
            avl.put(17, 17);
            avl.put(4, 4);
            assert avl.contains(8);
            avl.delete(8);
            assert !avl.contains(8);
            assert avl.root.value == 12;
            assert avl.root.left.value == 5;
            assert avl.root.left.right.value == 11;
            assert avl.root.left.left.value == 4;
            assert avl.root.right.value == 18;
            assert avl.root.right.left.value == 17;
            assert avl.root.right.right == null;
            System.out.println("success delete 8");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<Integer, Integer> avl = new AVL_Tree<>();

            avl.put(12, 12);
            avl.put(8, 8);
            avl.put(18, 18);
            avl.put(5, 5);
            avl.put(11, 11);
            avl.put(17, 17);
            avl.put(4, 4);
            assert avl.contains(18);
            avl.delete(18);
            assert !avl.contains(18);
            assert avl.root.value == 8;
            assert avl.root.left.value == 5;
            assert avl.root.left.right == null;
            assert avl.root.left.left.value == 4;
            assert avl.root.right.value == 12;
            assert avl.root.right.left.value == 11;
            assert avl.root.right.right.value == 17;
            System.out.println("success delete 18");
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<Integer, Integer> avl = new AVL_Tree<>();

            avl.put(12, 12);
            avl.put(8, 8);
            avl.put(18, 18);
            avl.put(5, 5);
            avl.put(11, 11);
            avl.put(17, 17);
            avl.put(4, 4);
            assert avl.contains(12);
            avl.delete(12);
            assert !avl.contains(12);
            assert avl.root.value == 8;
            assert avl.root.left.value == 5;
            assert avl.root.left.right == null;
            assert avl.root.left.left.value == 4;
            assert avl.root.right.value == 17;
            assert avl.root.right.left.value == 11;
            assert avl.root.right.right.value == 18;
            System.out.println("success delete 12");
        }
        System.out.println("---------------------------");
    }
}

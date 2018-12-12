//import java.util.NoSuchElementException;
import java.util.Random;

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

    private int balanceFactor(Node node) {
        return height(node.left) - height(node.right);
    }

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
        root.size = 1 + size(root.left) + size(root.right);
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

    public static void main(String[] args) {
        {
            AVL_Tree<Integer, String> bt = new AVL_Tree<>();

            // It's Greek to me.
            bt.put(5, "Cerberus");      // multi-headed dog that guards the gates of the Underworld
            bt.put(7, "Erebus");        // the god of darkness and shadow.
            bt.put(3, "Athena");        // goddess of reason, wisdom, intelligence, skill, peace, warfare...
            bt.put(4, "Bellerophon");   // hero who slew the Chimera
            bt.put(6, "Dryad");         // the nymphs of oak trees

            System.out.println("isEmpty: " + bt.isEmpty());
            System.out.println("size: " + bt.size());
            System.out.println("height: " + bt.height());
            System.out.println("avg height: " + bt.avgHeight());

            System.out.println("4: " + bt.get(4));
            System.out.println("14: " + bt.get(14));

            bt.inOrder();

            System.out.println("min: " + bt.min() + "   " + bt.get(bt.min()));
            System.out.println("min: " + bt.deleteMin() + "   " + bt.get(bt.min()));
            System.out.println("min: " + bt.deleteMin() + "   " + bt.get(bt.min()));
            System.out.println("min: " + bt.deleteMin() + "   " + bt.get(bt.min()));
            System.out.println("max: " + bt.max() + "   " + bt.get(bt.max()));
            System.out.println("max: " + bt.deleteMax() + "   " + bt.get(bt.max()));
            System.out.println("root: " + bt.root() + "   " + bt.get(bt.root()));
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<Integer, Integer> bt = new AVL_Tree<>();
            int min = Integer.MAX_VALUE;
            int max = Integer.MIN_VALUE;

            for (int i = 0; i < 100; i++) {
                min = 0;
                max = 99;
                bt.put(i, i);
            }
            System.out.println("size: " + bt.size());
            System.out.println("height: " + bt.height());
            System.out.println("avg height: " + bt.avgHeight());
            System.out.println("min: " + bt.min() + "   " + min);
            System.out.println("max: " + bt.max() + "   " + max);

            for (int i = 0; i < 10; i++) {
                System.out.print(bt.deleteMin() + ", ");
            }
            System.out.println("\nsize: " + bt.size());
            System.out.println("height: " + bt.height());
            System.out.println("avg height: " + bt.avgHeight());

            for (int i = 0; i < 10; i++) {
                System.out.print(bt.deleteMin() + ", ");
            }
            System.out.println("\nsize: " + bt.size());
            System.out.println("height: " + bt.height());
            System.out.println("avg height: " + bt.avgHeight());

            for (int i = 0; i < 10; i++) {
                System.out.print(bt.deleteMin() + ", ");
            }
            System.out.println("\nsize: " + bt.size());
            System.out.println("height: " + bt.height());
            System.out.println("avg height: " + bt.avgHeight());

            for (int i = 0; i < 10; i++) {
                System.out.print(bt.deleteMin() + ", ");
            }
            System.out.println("\nsize: " + bt.size());
            System.out.println("height: " + bt.height());
            System.out.println("avg height: " + bt.avgHeight());

            for (int i = 0; i < 10; i++) {
                System.out.print(bt.deleteMin() + ", ");
            }
            System.out.println("\nsize: " + bt.size());
            System.out.println("height: " + bt.height());
            System.out.println("avg height: " + bt.avgHeight());

            for (int i = 0; i < 10; i++) {
                System.out.print(bt.deleteMin() + ", ");
            }
            System.out.println("\nsize: " + bt.size());
            System.out.println("height: " + bt.height());
            System.out.println("avg height: " + bt.avgHeight());

            for (int i = 0; i < 10; i++) {
                System.out.print(bt.deleteMin() + ", ");
            }
            System.out.println("\nsize: " + bt.size());
            System.out.println("height: " + bt.height());
            System.out.println("avg height: " + bt.avgHeight());

            for (int i = 0; i < 10; i++) {
                System.out.print(bt.deleteMin() + ", ");
            }
            System.out.println("\nsize: " + bt.size());
            System.out.println("height: " + bt.height());
            System.out.println("avg height: " + bt.avgHeight());

            for (int i = 0; i < 10; i++) {
                System.out.print(bt.deleteMin() + ", ");
            }
            System.out.println("\nsize: " + bt.size());
            System.out.println("height: " + bt.height());
            System.out.println("avg height: " + bt.avgHeight());
        }
        System.out.println("---------------------------");
        {
            Random rand = new Random();
            int uBound = 1000000;
            Integer[] randInts = new Integer[uBound];

            rand.setSeed(333);
            for (int i = 0; i < uBound; i++) {
                randInts[i] = rand.nextInt(Integer.MAX_VALUE);
            }
            {
                AVL_Tree<Integer, Integer> bt = new AVL_Tree<>();

                for (int i = 0; i < uBound; i++) {
                    bt.put(randInts[i], i);
                }
                System.out.println("size: " + bt.size());
                System.out.println("height: " + bt.height());
                System.out.println("avg height: " + bt.avgHeight());

                for (int i = 0; i < 1000; i++) {
                    System.out.print(bt.deleteAtLocation(randInts[i]) + ", ");
                }
                System.out.println("\n size: " + bt.size());
                System.out.println("height: " + bt.height());
                System.out.println("avg height: " + bt.avgHeight());
            }
            {
                AVL_Tree<Integer, Integer> bt = new AVL_Tree<>();

                for (int i = uBound - 1; i >= 0; i--) {
                    bt.put(randInts[i], i);
                }
                System.out.println("size: " + bt.size());
                System.out.println("height: " + bt.height());
                System.out.println("avg height: " + bt.avgHeight());
            }
        }
        System.out.println("---------------------------");
        {
            AVL_Tree<Integer, Integer> bt = new AVL_Tree<>();
            for (int i = 0; i < 19000; i++) {
                bt.put(i, i);
            }
            System.out.println("size: " + bt.size());
            System.out.println("height: " + bt.height());
            System.out.println("avg height: " + bt.avgHeight());
        }
    }
}

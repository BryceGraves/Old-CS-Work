public class TriplyLinkedList {
    TriplyLinkedListNode root, temp;

    public TriplyLinkedList() { root = temp = null; }

    public boolean isEmpty() { return root == null; }

    public void makeEmpty() { root = temp = null; }

    public void insert(int x) { root = insert(root, x); }

    private TriplyLinkedListNode insert (TriplyLinkedListNode current, int x) {
        if (current == null) {
            current = new TriplyLinkedListNode(x);
            current.middle = temp;
        } else if (current.left == null) {
            current.weight++;
            temp = current;
            current.left = insert(current.left, x);
        } else if (current.right == null) {
            current.weight++;
            temp = current;
            current.right = insert(current.right, x);
        } else {
            current.weight++;
            if (current.left.weight == current.right.weight || current.left.weight % 2 == 1) {
                current.left = insert(current.left, x);
            } else {
                current.right = insert(current.right, x);
            }
        }
        swim(current);
        return (current);
    }

    public int remove(TriplyLinkedListNode current) {
        int toReturn = current.data;
        int dataToMove;

        while (current.left  != null && current.right != null) {
            if (current.left.weight == current.right.weight || current.right.weight % 2 == 1) {
                current = current.right;
            } else {
                current = current.left;
            }
        }

        if (current.left != null) {
            dataToMove = current.left.data;
            current.left = null;
        } else {
            dataToMove = current.data;
            current = current.middle;
            if (current.right != null) {
                current.right = null;
            } else {
                current.left = null;
            }
        }

        while (current.middle != null) {
            current.weight--;
            current = current.middle;
        }
        current.weight--;
        current.data = dataToMove;
        sink(current);
        return toReturn;
    }

    public void sink(TriplyLinkedListNode current) {
        int temp;
        while (current.left != null && current.right != null) {
            if (current.left.data < current.right.data) {
                if (current.data > current.left.data) {
                    temp = current.data;
                    current.data = current.left.data;
                    current.left.data = temp;
                    current = current.left;
                }
            } else {
                if (current.data > current.right.data) {
                    temp = current.data;
                    current.data = current.right.data;
                    current.right.data = temp;
                    current = current.right;
                }
            }
            break;
        }
        if (current.left != null) {
            if (current.data > current.left.data) {
                temp = current.data;
                current.data = current.left.data;
                current.left.data = temp;
                current = current.left;
            }
        }
        return;
    }

    public void swim(TriplyLinkedListNode current) {
        if (current.middle == null) { return; }

        while (current.middle != null && current.data < current.middle.data) {
            int dataSwap = current.data;
            current.data = current.middle.data;
            current.middle.data = dataSwap;
            current = current.middle;
        }
    }

    public void printList() { printList(root); StdOut.println(); }

    private void printList(TriplyLinkedListNode current) {
        if (current != null) {
            printList(current.left);
            StdOut.print(current.data + " ");
            printList(current.right);
        }
    }

    public void min() { min(root); StdOut.println(); }

    private void min(TriplyLinkedListNode current) {
        StdOut.print(current.data);
    }

    public int size() { return size(root); }

    private int size(TriplyLinkedListNode list) {
        return list.weight + 1;
    }
}

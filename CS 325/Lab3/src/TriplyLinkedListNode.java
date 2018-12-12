public class TriplyLinkedListNode {
    TriplyLinkedListNode left, right, middle;
    int data;
    int weight;

    /* Constructor */
    public TriplyLinkedListNode(int x) {
        data = x;
        weight = 0;
        left = right = middle = null;
    }
}

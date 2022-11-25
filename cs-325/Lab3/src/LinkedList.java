public class LinkedList {
    LinkedListNode head;

    public void push(int x) {
        LinkedListNode newNode = new LinkedListNode(x);
        newNode.next = head;
        head = newNode;
    }

    public LinkedListNode mergeSort(LinkedListNode head) {
        if (head == null || head.next == null) { return head; }

        LinkedListNode middle = getMiddle(head);
        LinkedListNode half = middle.next;
        middle.next = null;

        return merge(mergeSort(head), mergeSort(half));
    }

    public LinkedListNode merge(LinkedListNode a, LinkedListNode b) {
        LinkedListNode temp, current;
        current = temp = new LinkedListNode(-1);

        while (a != null && b != null) {
            if (a.data <= b.data) { current.next = a; a = a.next; }
            else { current.next = b; b = b.next; }
            current = current.next;
        }

        current.next = (a == null) ? b : a;
        return temp.next;
    }

    public LinkedListNode getMiddle(LinkedListNode head) {
        if (head == null) { return head; }

        LinkedListNode moveOne, moveTwo;
        moveOne = moveTwo = head;

        while (moveTwo.next != null && moveTwo.next.next != null) {
            moveOne = moveOne.next;
            moveTwo = moveTwo.next.next;
        }

        return moveOne;
    }


    public static void printList(LinkedListNode head) {
        LinkedListNode current = head;
        while (current != null) {
            StdOut.print(current.data + " ");
            current = current.next;
        }
    }
}

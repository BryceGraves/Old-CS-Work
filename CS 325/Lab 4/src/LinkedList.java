import java.util.Iterator;
import java.util.NoSuchElementException;

public class LinkedList<Item extends Comparable> implements Iterable<Item>  {
    private Node first;
    private Node last;
    private int size;

    private class Node {
        private Item data;
        private Node next;

        private Node(){ }

        public Node(Item dat) {
            data = dat;
            next = null;
        }
    }

    public LinkedList(){
        first = null;
        last = null;
        size = 0;
    };

    public LinkedList(Item item){
        first = new Node(item);
        last = first;
        size = 1;
    };

    public void addFirst(Item item) {
        Node nn = new Node(item);

        nn.next = first;
        first = nn;
        if (last == null) {
            last = first;
        }
        size++;
    }

    public void addLast(Item item) {
        if (first == null) {
            addFirst(item);
        }
        else {
            Node nn = new Node(item);
            last.next = nn;
            last = nn;
            size++;
        }
    }

    public Item removeFirst() {
        if (first == null) {
            throw new NoSuchElementException("removeFirst: empty list");
        }

        Item i = first.data;
        first = first.next;
        if (first == null)
            last = first;
        size--;
        return i;
    }

    public Item first() {
        if (first == null) {
            throw new NoSuchElementException("removeFirst: empty list");
        }

        Item i = first.data;
        return i;
    }

    public Item removeLast() {
        if (first == null) {
            throw new NoSuchElementException("removeLast: empty list");
        }

        Node curr;
        Node trailer;
        for (curr = first, trailer = null ;
             curr.next != null ;
             trailer = curr, curr = curr.next);

        Item i = curr.data;
        last = trailer;
        if (last != null)
            last.next = null;
        else
            first = null;

        size--;
        return i;
    }

    public boolean remove(Item item) {
        if (first == null) {
            throw new NoSuchElementException("remove: empty list");
        }
        boolean retVal = false;
        Node curr = first;
        Node trailer = null;

        while (curr != null) {
            if (item.compareTo(curr.data) == 0) {
                if (trailer == null) {
                    // this is the head of the list.
                    first = curr.next;
                }
                else {
                    if (curr.next == null) {
                        // this is the last in the list.
                        trailer.next = null;
                        last = trailer;
                    }
                    else {
                        trailer.next = curr.next;
                    }
                }
                size--;
                break;
            }
            trailer = curr;
            curr = curr.next;
        }

        return retVal;
    }

    public boolean contains(Item item) {
        boolean retVal = false;
        Node curr = first;
        Node trailer = null;

        while (curr != null) {
            if (item.compareTo(curr.data) == 0) {
                retVal = true;
                break;
            }
            trailer = curr;
            curr = curr.next;
        }

        return retVal;
    }

    // Not tested yet.
    public boolean contains(Item item, boolean deleteIfFound) {
        boolean retVal = false;

        if (deleteIfFound)
            retVal = remove(item);
        else
            retVal = contains(item);

        return retVal;
    }

    public Item peekFirst() {
        return first.data;
    }

    public Item peekLast() {
        return last.data;
    }

    public boolean isEmpty() {
        return first == null;
    }

    public int size() {
        return size;
    }

    public Iterator<Item> iterator() {
        return new ListIterator();
    }

    private class ListIterator implements Iterator<Item> {
        private Node current = first;
        public boolean hasNext() {
            return current != null;
        }
        public Item next() {
            if (!hasNext()) {
                // barf
                throw new NoSuchElementException("trying to iterate here");
            }
            Item item = current.data;
            current = current.next;

            return item;
        }
    }

    public String toString() {
        StringBuilder s = new StringBuilder();

        for (Item i: this) {
            s.append(i + " ");
        }

        return s.toString();
    }

    public static void main(String[] args) {
        // make sure you have the -ea option set for the VM options in the runtime config.
        //
        // If you want to make sure the assert statements are enabled, uncomment the
        // following line. It should always fail.
        // assert false;
        //
        {
            LinkedList<Integer> ll = new LinkedList<Integer>();

            assert ll.first == null && ll.last == null;
            assert ll.size == 0;
            assert ll.isEmpty() == true;
            assert !ll.contains(0);

            ll.addLast(5);
            assert ll.contains(5);
            assert ll.isEmpty() == false;
            assert ll.first != null && ll.last != null;
            assert ll.size == 1;
            assert ll.first.data == 5;
            assert ll.first.next == null;

            Integer i = ll.removeFirst();
            assert !ll.contains(5);
            assert ll.first == null && ll.last == null;
            assert ll.size == 0;
        }
        {
            LinkedList<Integer> ll = new LinkedList<Integer>();
            ll.addLast(5);
            assert ll.first != null && ll.last != null;
            assert ll.size == 1;
            assert ll.first.data == 5;
            assert ll.first.next == null;

            Integer i = ll.removeLast();
            assert ll.first == null && ll.last == null;
            assert ll.size == 0;
        }
        {
            LinkedList<Integer> ll = new LinkedList<Integer>();
            ll.addLast(5);
            ll.addLast(15);
            assert ll.first != null && ll.last != null;
            assert ll.size == 2;
            assert ll.first.data == 5;
            assert ll.last.data == 15;
            assert ll.last == ll.first.next;

            assert ll.peekFirst() == ll.first.data;
            assert ll.size == 2;
            assert ll.peekFirst() == ll.first.data;
            assert ll.size == 2;

            assert ll.peekLast() == ll.last.data;
            assert ll.size == 2;
            assert ll.peekLast() == ll.last.data;
            assert ll.size == 2;

            Integer i = ll.removeFirst();
            assert ll.first != null && ll.last != null;
            assert ll.size == 1;
            assert ll.first.data == 15;
            assert ll.first.next == null;
            assert ll.last != null;

            assert ll.peekFirst() == ll.first.data;
            assert ll.size == 1;
            assert ll.peekFirst() == ll.first.data;
            assert ll.size == 1;

            assert ll.peekLast() == ll.last.data;
            assert ll.size == 1;
            assert ll.peekLast() == ll.last.data;
            assert ll.size == 1;
        }
        {
            LinkedList<Integer> ll = new LinkedList<Integer>();
            ll.addLast(5);
            ll.addLast(15);
            Integer i = ll.removeLast();
            assert ll.first != null && ll.last != null;
            assert ll.size == 1;
            assert ll.first.data == 5;
            assert ll.peekFirst() == ll.first.data;
            assert ll.first.next == null;
            assert ll.last != null;
            assert ll.peekFirst() == ll.peekLast();
        }
        {
            LinkedList<Integer> ll = new LinkedList<Integer>();
            ll.addFirst(5);
            ll.addFirst(15);
            assert ll.first != null && ll.last != null;
            assert ll.size == 2;
            assert ll.first.data == 15;
            assert ll.last.data == 5;
            assert ll.last == ll.first.next;
            assert ll.peekFirst() != ll.peekLast();

            assert ll.peekFirst() == ll.first.data;
            assert ll.peekLast() == ll.last.data;

            Integer i = ll.removeFirst();
            assert ll.first != null && ll.last != null;
            assert ll.size == 1;
            assert ll.first.data == 5;
            assert ll.first.next == null;
            assert ll.last != null;
        }
        {
            LinkedList<Integer> ll = new LinkedList<Integer>();
            ll.addFirst(5);
            ll.addFirst(15);
            Integer i = ll.removeLast();
            assert ll.first != null && ll.last != null;
            assert ll.size == 1;
            assert ll.first.data == 15;
            assert ll.first.next == null;
            assert ll.last != null;
        }
        Integer[] test = {5,9,2,12};
        {
            LinkedList<Integer> ll = new LinkedList<Integer>();

            for (int i = 0; i < test.length; i++) {
                ll.addLast(test[i]);
            }

            assert ll.first != null && ll.last != null;
            assert ll.size == 4;
            assert ll.size == ll.size();
            assert ll.first.data == 5;
            assert ll.last.data == 12;
            assert ll.first.next.data == 9;

            System.out.println("size: " + ll.size());
            System.out.println(ll.toString());

            assert ll.contains(9);
            ll.remove(9);
            assert !ll.contains(9);
            assert ll.size == 3;
            assert ll.first.data == 5;
            assert ll.last.data == 12;
            assert ll.first.next.data == 2;

            assert ll.contains(5);
            ll.remove(5);
            assert !ll.contains(5);

            assert ll.contains(12);
            ll.remove(12);
            assert !ll.contains(12);

            assert ll.contains(2);
            assert ll.size == 1;

            System.out.println("size: " + ll.size());
            System.out.println(ll.toString());
        }
        {
            LinkedList<Integer> ll = new LinkedList<Integer>();
            for (int i = 0; i < 100; i++) {
                ll.addLast(3);
            }
            assert ll.size() == 100;
            ll.remove(3);
            assert ll.contains(3);
            assert ll.size() == 99;
        }
        {
            LinkedList<Integer> ll = new LinkedList<Integer>();
            for (int i = 0; i < test.length; i++) {
                ll.addLast(test[i]);
            }

            int i = 0;
            for (int j : ll) {
                assert j == test[i++];
            }
        }
        {
            LinkedList<Integer> ll = new LinkedList<Integer>();
            for (int i = 0; i < test.length; i++) {
                ll.addFirst(test[i]);
            }

            int i = 3;
            for (int j : ll) {
                assert j == test[i--];
            }
        }
        {
            LinkedList<String> ll = new LinkedList<String>();

            ll.addFirst("Jill");
            ll.addLast("Joanna");
            ll.addFirst("Dan");
            ll.addFirst("Yong");
            ll.addLast("Jesse");

            System.out.println(ll.toString());
            ll.remove("Jesse");
            System.out.println(ll.toString());
        }
    }
}

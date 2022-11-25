import java.util.Arrays;
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
        {
            LinkedList<Integer> ll = new LinkedList<Integer>();

            assert ll.first == null && ll.last == null;
            assert ll.size == 0;
            assert ll.isEmpty() == true;

            ll.addLast(5);
            assert ll.isEmpty() == false;
            assert ll.first != null && ll.last != null;
            assert ll.size == 1;
            assert ll.first.data == 5;
            assert ll.first.next == null;

            Integer i = ll.removeFirst();
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

            Integer i = ll.removeFirst();
            assert ll.first != null && ll.last != null;
            assert ll.size == 1;
            assert ll.first.data == 15;
            assert ll.first.next == null;
            assert ll.last != null;
        }
        {
            LinkedList<Integer> ll = new LinkedList<Integer>();
            ll.addLast(5);
            ll.addLast(15);
            Integer i = ll.removeLast();
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
            assert ll.first != null && ll.last != null;
            assert ll.size == 2;
            assert ll.first.data == 15;
            assert ll.last.data == 5;
            assert ll.last == ll.first.next;

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

            ll.remove(9);
            assert ll.size == 3;
            assert ll.first.data == 5;
            assert ll.last.data == 12;
            assert ll.first.next.data == 2;
            System.out.println("size: " + ll.size());
            System.out.println(ll.toString());
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

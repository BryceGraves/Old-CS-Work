public class Queue<Item extends Comparable> extends LinkedList<Item> {
    public void enqueue(Item item) {
        addLast(item);
    }
    public Item dequeue() {
        return removeFirst();
    }
    public Item peek() {
        return peekFirst();
    }

    public static void main(String[] args) {
        {
            Queue<Integer> queue = new Queue<Integer>();

            for (int i = 0; i < 5; i++) {
                queue.enqueue(i);
            }
            Integer i = queue.peek();
            assert queue.size() == 5;
            assert queue.peek() == i;
            {
                Integer j = queue.dequeue();
                assert j == i;
                assert queue.size() == 4;
            }

            i = queue.dequeue();
            assert i == 1;
            assert queue.size() == 3;

            i = queue.dequeue();
            assert i == 2;
            assert queue.size() == 2;

            i = queue.dequeue();
            assert i == 3;
            assert queue.size() == 1;
        }
        {
            Queue<Integer> queue = new Queue<Integer>();

            for (int i = 0; i < 5; i++) {
                queue.enqueue(i);
            }
            System.out.println("queue: " + queue.toString());
            Integer i = queue.dequeue();
            System.out.println("item: " + i);
            System.out.println("queue: " + queue.toString());

            System.out.println(queue.toString());
        }
        Integer[] primes = {2,3,5,7,11,13,17,19,23,27,31};
        {
            Queue<Integer> queue = new Queue<Integer>();

            assert queue.size() == 0;
            assert queue.isEmpty();

            for (int i : primes) {
                queue.enqueue(i);
            }
            assert queue.size() == primes.length;
            assert !queue.isEmpty();
        }
        {
            Queue<Integer> queue = new Queue<Integer>();

            for (int i : primes) {
                queue.enqueue(i);
            }
            {
                int j = 0;
                for (int i : queue) {
                    assert i == primes[j++];
                }
            }
            {
                int j = 0;
                assert !queue.isEmpty();
                for (int i : queue) {
                    assert queue.dequeue().equals(primes[j++]);
                }
            }
            assert queue.isEmpty();
            assert queue.size() == 0;
        }
    }
}

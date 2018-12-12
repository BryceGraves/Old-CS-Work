public class Stack<Item extends Comparable> extends LinkedList<Item> {
    public void push(Item item) {
        addFirst(item);
    }
    public Item pop() {
        return removeFirst();
    }
    public Item peek() {
        return peekFirst();
    }

    public static void main(String[] args) {
        {
            Stack<Integer> stack = new Stack<Integer>();

            for (int i = 0; i < 5; i++) {
                stack.push(i);
            }
            Integer i = stack.peek();
            assert stack.size() == 5;
            assert stack.peek() == 4;
            {
                Integer j = stack.pop();
                assert j == i;
                assert stack.size() == 4;
            }

            i = stack.pop();
            assert i == 3;
            assert stack.size() == 3;

            i = stack.pop();
            assert i == 2;
            assert stack.size() == 2;

            i = stack.pop();
            assert i == 1;
            assert stack.size() == 1;
        }
        {
            Stack<Integer> stack = new Stack<Integer>();

            for (int i = 0; i < 5; i++) {
                stack.push(i);
            }
            System.out.println("stack: " + stack.toString());
            Integer i = stack.pop();
            System.out.println("item: " + i);
            System.out.println("stack: " + stack.toString());

            System.out.println(stack.toString());
        }
        Integer[] primes = {2,3,5,7,11,13,17,19,23,27,31};
        {
            Stack<Integer> stack = new Stack<Integer>();

            assert stack.size() == 0;
            assert stack.isEmpty();

            for (int i : primes) {
                stack.push(i);
            }
            assert stack.size() == primes.length;
            assert !stack.isEmpty();
        }
        {
            Stack<Integer> stack = new Stack<Integer>();

            for (int i : primes) {
                stack.push(i);
            }
            {
                int j = primes.length - 1;
                for (int i : stack) {
                    assert i == primes[j--];
                }
            }
            {
                int j = primes.length - 1;
                assert !stack.isEmpty();
                for (int i : stack) {
                    assert stack.pop().equals(primes[j--]);
                }
            }
            assert stack.isEmpty();
            assert stack.size() == 0;
        }
    }
}

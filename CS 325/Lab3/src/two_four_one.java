import java.util.Collections;
import java.util.PriorityQueue;

public class two_four_one {
    public static void main(String[] arg) {
        //  P R I O * R * * I * T * Y * * * Q U E * * *
        //  U * E
        PriorityQueue<String> queue = new PriorityQueue<>(Collections.reverseOrder());
        queue.add("P");
        queue.add("R");
        queue.add("I");
        queue.add("O");
        StdOut.print(queue.remove());
        queue.add("R");
        StdOut.print(queue.remove());
        StdOut.print(queue.remove());
        queue.add("I");
        StdOut.print(queue.remove());
        queue.add("T");
        StdOut.print(queue.remove());
        queue.add("Y");
        StdOut.print(queue.remove());
        StdOut.print(queue.remove());
        StdOut.print(queue.remove());
        queue.add("Q");
        queue.add("U");
        queue.add("E");
        StdOut.print(queue.remove());
        StdOut.print(queue.remove());
        StdOut.print(queue.remove());
        queue.add("U");
        StdOut.print(queue.remove());
        queue.add("E");
    }
}

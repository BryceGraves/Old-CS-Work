public class GenData {
    private static final int MILLION = 1000000;

    public static void main(String[] args) {
        for(Integer n = 1; n <= 64; n *= 2) {
            int N = n * MILLION;
            String fileName = n.toString() + "Mints.txt";
            StdOut.println(fileName);
            Out file = new Out(fileName);

            for (int i = 0; i < N; i ++) {
                int x = StdRandom.uniform(-100 * MILLION, 100 * MILLION + 1);

                file.printf("%d\n", x);
            }

            file.close();
        }
    }
}

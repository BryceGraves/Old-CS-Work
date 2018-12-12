public class Main {
    public static void main(String[] args) {
            for (Integer N = 1; N <= 512; N *= 2) {
                String fn = N.toString() + "Kuf.txt";
                In in = new In(fn);
                int n = in.readInt();
                double loadTime = 0.0;
                QuickFindUF uf = new QuickFindUF(n);
                {
                    Stopwatch timer = new Stopwatch();
                    int counter = 0;
                    while (!in.isEmpty()) {
                        int p = in.readInt();
                        int q = in.readInt();
                        if (uf.connected(p, q))
                            continue;
                        uf.union(p, q);
                        counter++;
                    }
                    loadTime = timer.elapsedTime();
                }
                in.close();
                {
                    long connectCount = 0;
                    long connectCheck = 0;
                    Stopwatch timer = new Stopwatch();
                    for (int i = 0; i < n; i += 3) {
                        for (int j = 1; j < n; j *= 2) {
                            connectCheck++;
                            if (uf.connected(i, j)) {
                                connectCount++;
                            }
                        }
                    }
                    StdOut.printf("%d\t%.3f\t%.3f\t%d\t%d\n", n, loadTime
                            , timer.elapsedTime(), connectCount, connectCheck);
            }
        }
    }
}

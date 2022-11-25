public class DigraphTopoSort {
    private Iterable<Integer> order;
    private Iterable<Integer> rorder;
    private int[] rank;

    public DigraphTopoSort(Digraph graph) {
        DigraphCycle finder = new DigraphCycle(graph);

        if (!finder.hasCycle()) {
            DepthFirstOrder dfs = new DepthFirstOrder(graph);

            order = dfs.reversePost();
            rorder = dfs.post();
            rank = new int[graph.V()];
            int i = 0;
            for (int v : order) {
                rank[v] = i++;
            }
        }
    }

    public Iterable<Integer> order() {
        return order;
    }

    public Iterable<Integer> rorder() {
        return rorder;
    }

    public boolean hasOrder() {
        return order != null;
    }

    public int rank(int v) {
        if (validVertex(v)) {
            if (hasOrder())
                return rank[v];
            else
                return -1;
        }

        throw new IllegalArgumentException("rank: invalid vertex");
    }

    private boolean validVertex(int vert) {
        return (vert >= 0 && vert < rank.length);
    }

    public static void main(String[] args) {
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            String fName = "tinyDG.txt";
            Digraph g = new Digraph(fName);

            DigraphTopoSort s = new DigraphTopoSort(g);
            System.out.println(fName + " have Toposort: " + s.hasOrder());
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            String fName = "tinyDAG0.txt";
            Digraph g = new Digraph(fName);

            DigraphTopoSort s = new DigraphTopoSort(g);
            System.out.println(fName + " have Toposort: " + s.hasOrder());

            for (int v : s.order()) {
                System.out.println("  " + v);
            }
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            String fName = "tinyDAG1.txt";
            Digraph g = new Digraph(fName);

            DigraphTopoSort s = new DigraphTopoSort(g);
            System.out.println(fName + " have Toposort: " + s.hasOrder());

            for (int v : s.order()) {
                System.out.println("  " + v);
            }
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            String fName = "Classes.txt";
            Digraph g = new Digraph(fName);

            DigraphTopoSort s = new DigraphTopoSort(g);
            System.out.println(fName + " have Toposort: " + s.hasOrder());

            int i = 1;
            for (int v : s.order()) {
                System.out.println(i + "  " + v);
                i++;
            }
            System.out.println("-----");

            for (int v : s.rorder()) {
                System.out.println("  " + v);
            }
        }
    }
}

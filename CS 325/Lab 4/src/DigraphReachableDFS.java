public class DigraphReachableDFS {
    private final int srcVertex;
    private boolean[] marked;
    private int[] edgeTo;
    private int count;

    public DigraphReachableDFS(Digraph graph, int src) {
        srcVertex = src;
        count = 0;
        marked = new boolean[graph.V()];
        edgeTo = new int[graph.V()];
        if (validVertex(src)) {
            edgeTo[src] = -1;
            dfs(graph, src);
        }
        else {
            throw new IllegalArgumentException("DigraphReachableDFS: invalid vertex");
        }
    }

    private boolean validVertex(int vert) {
        return (vert >= 0 && vert < marked.length);
    }

    private void dfs(Digraph graph, int v) {
        marked[v] = true;
        for (int w: graph.edgesOut(v)) {
            if (!marked[w]) {
                count++;
                edgeTo[w] = v;
                dfs(graph, w);
            }
        }
    }

    public boolean hasPathTo(int w) {
        if (validVertex(w)) {
            return marked[w];
        }
        else {
            throw new IllegalArgumentException("hasPathTo: invalid vertex");
        }
    }

    public Iterable<Integer> pathTo(int w) {
        LinkedList<Integer> path = null;
        if (validVertex(w)) {
            if (hasPathTo(w)) {
                path = new LinkedList<Integer>();
                for (int i = w; i != srcVertex; i = edgeTo[i]) {
                    path.addFirst(i);
                }
                path.addFirst(srcVertex);
            }
        }
        else {
            throw new IllegalArgumentException("pathTo: invalid vertex");
        }
        return path;
    }

    public static void main(String[] args) {
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            Integer src = 0;
            Digraph g = new Digraph("tinyDG.txt");
            DigraphReachableDFS gp = new DigraphReachableDFS(g, src);

            System.out.println("path between " + src + " and 2:  " + gp.hasPathTo(2));
            System.out.println("path between " + src + " and 12: " + gp.hasPathTo(12));

            assert gp.hasPathTo(2);
            assert !gp.hasPathTo(12);

            System.out.print("Path from " + src + " to 2: ");
            int[] vals = {0, 5, 4, 2};
            int j = 0;
            for (int i: gp.pathTo(2)) {
                assert i == vals[j++];
                if (i == src)
                    System.out.print(i);
                else
                    System.out.print(" -> " + i);
            }
            System.out.println();
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            Integer src = 3;
            Digraph g = new Digraph("tinyDG.txt");
            DigraphReachableDFS gp = new DigraphReachableDFS(g, src);

            System.out.println("path between " + src + " and 0:  " + gp.hasPathTo(0));
            System.out.println("path between " + src + " and 1:  " + gp.hasPathTo(1));
            System.out.println("path between " + src + " and 12: " + gp.hasPathTo(12));
            assert gp.hasPathTo(0) == true;
            assert gp.hasPathTo(12) == false;

            System.out.print("Path from " + src + " to 1: ");
            for (int i: gp.pathTo(1)) {
                if (i == 3)
                    System.out.print(i);
                else
                    System.out.print(" -> " + i);
            }
            System.out.println();
            System.out.print("Path from " + src + " to 2: ");
            for (int i: gp.pathTo(2)) {
                if (i == src)
                    System.out.print(i);
                else
                    System.out.print(" -> " + i);
            }
            System.out.println();
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
    }
}

public class DigraphReachableBFS {
    private static final int BIG_LEBOWSKI = Integer.MAX_VALUE;
    private boolean[] marked;
    private int[] edgeTo;       // edgeTo[v] = previous edge on shortest s-v path
    private int[] distTo;

    public DigraphReachableBFS(Digraph graph, int src) {
        marked = new boolean[graph.V()];
        distTo = new int[graph.V()];
        edgeTo = new int[graph.V()];
        validVertex(src);
        bfs(graph, src);
    }

    public DigraphReachableBFS(Digraph graph, Iterable<Integer> sources) {
        marked = new boolean[graph.V()];
        distTo = new int[graph.V()];
        edgeTo = new int[graph.V()];

        for (int i: sources) {
            if (!validVertex(i)) {
                // barf
                throw new IllegalArgumentException("DigraphReachableBFS: invalid vertex");
            }
        }
        bfs(graph, sources);
    }

    private boolean validVertex(int vert) {
        return (vert >= 0 && vert < marked.length);
    }

    private void bfs(Digraph graph, int src) {
        LinkedList<Integer> theQ = new LinkedList<Integer>();
        for (int v = 0; v < marked.length; v++) {
            distTo[v] = BIG_LEBOWSKI;
        }
        distTo[src] = 0;
        marked[src] = true;
        theQ.addFirst(src);

        while (!theQ.isEmpty()) {
            int v = theQ.removeLast();
            for (int w: graph.edgesOut(v)) {
                if (!marked[w]) {
                    edgeTo[w] = v;
                    distTo[w] = distTo[v] + 1;
                    marked[w] = true;
                    theQ.addFirst(w);
                }
            }
        }
    }

    private void bfs(Digraph graph, Iterable<Integer> sources) {
        LinkedList<Integer> theQ = new LinkedList<Integer>();
        for (int v = 0; v < marked.length; v++) {
            distTo[v] = BIG_LEBOWSKI;
        }
        for (int s : sources) {
            marked[s] = true;
            distTo[s] = 0;
            theQ.addFirst(s);
        }

        while (!theQ.isEmpty()) {
            int v = theQ.removeLast();
            for (int w: graph.edgesOut(v)) {
                if (!marked[w]) {
                    edgeTo[w] = v;
                    distTo[w] = distTo[v] + 1;
                    marked[w] = true;
                    theQ.addFirst(w);
                }
            }
        }
    }

    public boolean hasPathTo(int w) {
        if (validVertex(w)) {
            return marked[w];
        }
        else
            throw new IllegalArgumentException("barf");
    }

    public int distTo(int w) {
        if (validVertex(w)) {
            return distTo[w];
        }
        else {
            throw new IllegalArgumentException("barf");
        }
    }

    public Iterable<Integer> pathTo(int w) {
        LinkedList<Integer> path = null;
        if (validVertex(w)) {
            if (hasPathTo(w)) {
                int x;
                path = new LinkedList<Integer>();
                for (x = w; distTo[x] != 0; x = edgeTo[x]) {
                    path.addFirst(x);
                }
                path.addFirst(x);
            }
        }
        else {
            throw new IllegalArgumentException("barf");
        }
        //System.out.println(">>> path length: " + path.size());
        return path;
    }

    public static void main(String[] args) {
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            Integer src = 0;
            Digraph g = new Digraph("tinyDG.txt");
            DigraphReachableBFS gp = new DigraphReachableBFS(g, src);

            System.out.println("path between " + src + " and 2:  " + gp.hasPathTo(2));
            System.out.println("path between " + src + " and 12: " + gp.hasPathTo(12));
            assert gp.hasPathTo(2) == true;
            assert gp.hasPathTo(12) == false;

            System.out.println("dist between " + src + " and 2: " + gp.distTo(2));
            System.out.println("dist between " + src + " and 12: " + gp.distTo(12));

            System.out.print("Shortest path from " + src + " to 2: ");
            for (int i: gp.pathTo(2)) {
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
            DigraphReachableBFS gp = new DigraphReachableBFS(g, src);

            System.out.println("path between " + src + " and 0:  " + gp.hasPathTo(0));
            System.out.println("path between " + src + " and 1:  " + gp.hasPathTo(1));
            System.out.println("path between " + src + " and 12: " + gp.hasPathTo(12));
            assert gp.hasPathTo(0) == true;
            assert gp.hasPathTo(12) == false;

            System.out.println("dist between " + src + " and 2: " + gp.distTo(2));
            System.out.println("dist between " + src + " and 12: " + gp.distTo(12));

            System.out.print("Shortest path from " + src + " to 2: ");
            for (int i: gp.pathTo(2)) {
                if (i == src)
                    System.out.print(i);
                else
                    System.out.print(" -> " + i);
            }
            System.out.println();
            System.out.print("Shortest path from " + src + " to 1: ");
            for (int i: gp.pathTo(1)) {
                if (i == src)
                    System.out.print(i);
                else
                    System.out.print(" -> " + i);
            }
            System.out.println();
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            LinkedList<Integer> srcs = new LinkedList<>();
            srcs.addLast(0);
            srcs.addLast(3);
            Digraph g = new Digraph("tinyDG.txt");
            DigraphReachableBFS gp = new DigraphReachableBFS(g, srcs);

            System.out.println("path to 1:  " + gp.hasPathTo(1));
            System.out.println("path to 12: " + gp.hasPathTo(12));
            assert gp.hasPathTo(0) == true;
            assert gp.hasPathTo(12) == false;

            System.out.println("dist to 2: " + gp.distTo(2));
            System.out.println("dist to 12: " + gp.distTo(12));

            System.out.print("Shortest path to 2: ");
            for (int i: gp.pathTo(2)) {
                System.out.print(" -> " + i);
            }
            System.out.println();

            System.out.print("Shortest path to 4: ");
            for (int i: gp.pathTo(4)) {
                System.out.print(" -> " + i);
            }
            System.out.println();
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            LinkedList<Integer> srcs = new LinkedList<>();
            srcs.addLast(1);
            srcs.addLast(7);
            srcs.addLast(10);
            Digraph g = new Digraph("tinyDG.txt");
            DigraphReachableBFS gp = new DigraphReachableBFS(g, srcs);

            System.out.println("path to 4:  " + gp.hasPathTo(4));
            System.out.println("path to 12: " + gp.hasPathTo(12));

            System.out.println("dist to 4: " + gp.distTo(4));
            System.out.println("dist to 5: " + gp.distTo(4));
            System.out.println("dist to 5: " + gp.distTo(12));

            System.out.print("Shortest path to 4: ");
            for (int i: gp.pathTo(4)) {
                System.out.print(" -> " + i);
            }
            System.out.println();

            System.out.print("Shortest path to 5: ");
            for (int i: gp.pathTo(5)) {
                System.out.print(" -> " + i);
            }
            System.out.println();

            System.out.print("Shortest path to 12: ");
            for (int i: gp.pathTo(12)) {
                System.out.print(" -> " + i);
            }
            System.out.println();
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
    }
}

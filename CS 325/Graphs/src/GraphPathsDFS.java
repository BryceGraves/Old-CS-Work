public class GraphPathsDFS {
    private final int srcVertex;
    private boolean[] marked;
    private int[] edgeTo;

    public GraphPathsDFS(GraphLists graph, int src) {
        srcVertex = src;
        edgeTo = new int[graph.V()];
        marked = new boolean[graph.V()];
        if (validVertex(src)) {
            //edgeTo[src] = -1;
            dfs(graph, src);
        }
        else {
            throw new IllegalArgumentException("GraphPathsDFS: invalid vertex");
        }
    }

    private void dfs(GraphLists graph, int v) {
        marked[v] = true;
        for (int w: graph.adjVerts(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                dfs(graph, w);
            }
        }
    }

    public boolean hasPathTo(int w) {
        if (validVertex(w)) {
            return marked[w];
        }
        else
            throw new IllegalArgumentException("hasPathTo: invalid vertex");
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

    private boolean validVertex(int vert) {
        return (vert >= 0 && vert < marked.length);
    }

    public static void main(String[] args) {
        {
            GraphLists g = new GraphLists("tinyG2.txt");
            GraphPathsDFS gp = new GraphPathsDFS(g, 0);

            System.out.println("path between 0 and 3:  " + gp.hasPathTo(3));
            System.out.println("path between 0 and 12: " + gp.hasPathTo(12));

            System.out.print("Path from 0 to 3: ");
            for (int i: gp.pathTo(3)) {
                if (i == 0)
                    System.out.print(i);
                else
                    System.out.print(" -> " + i);
            }
            System.out.println();
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            GraphLists g = new GraphLists("tinyG.txt");
            GraphPathsDFS gp = new GraphPathsDFS(g, 0);

            System.out.println("path between 0 and 3:  " + gp.hasPathTo(3));
            System.out.println("path between 0 and 12: " + gp.hasPathTo(12));

            System.out.print("Path from 0 to 3: ");
            for (int i: gp.pathTo(3)) {
                if (i == 0)
                    System.out.print(i);
                else
                    System.out.print(" -> " + i);
            }
            System.out.println();
        }
    }
}

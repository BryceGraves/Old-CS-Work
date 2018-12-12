import java.util.LinkedList;

public class GraphPathBFS {

    private static final int BIG_LABOWSKY = Integer.MAX_VALUE;
    private boolean[] marked;
    private int[] edgeTo;
    private int[] distTo;

    public GraphPathBFS(GraphLists graph, int src) {
        marked = new boolean[graph.numOfVert()];
        distTo = new int[graph.numOfVert()];
        edgeTo = new int[graph.numOfEdge()];

        validVertex(src);
        bfs(graph, src);
    }


    private void bfs(GraphLL graph, int src) {
        LinkedList<Integer> theQ = new LinkedList<>();

        for(int v = 0; v < marked.length; v++) {
            distTo[v] = BIG_LABOWSKY;
        }

        distTo[src] = 0;
        marked[src] = true;
        theQ.addFirst(src);

        while(!theQ.isEmpty()) {
            int v = theQ.removeLast();
            for(int w: graph.adjVerts(v)) {
                if(!marked[w]) {
                    marked[w] = true;
                    edgeTo[w] = v;
                    distTo[w] = distTo[v] + 1;
                    theQ.addFirst(w);
                }
            }

        }
    }

    /***********
     * methods
     */
    public boolean hasPathTo(int w) {
        //check for validity of w
        if(validVertex(w)) {
            return marked[w];
        }
        return false;
    }

    public int distTo(int w) {
        if(validVertex(w)) {
            return distTo[w];
        }
        return BIG_LABOWSKY;
    }

    public Iterable<Integer> pathTo(int w) {
        LinkedList<Integer> path = null;

        if(validVertex(w)) {
            if(hasPathTo(w)) {
                int x;
                path = new LinkedList<>();
                for(x = w; distTo[w] != 0; x = edgeTo[x]) {
                    path.addFirst(x);
                }
                path.addFirst(x);
            }
        }
        return path;
    }

    /*************
     * helper functions
     */
    private boolean validVertex(int v) {
        return (v >= 0 && v < marked.length);
    }
}

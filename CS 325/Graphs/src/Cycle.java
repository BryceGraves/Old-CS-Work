import java.util.LinkedList;

public class Cycle {

    private boolean[] marked;
    private int[] edgeTo;
    private LinkedList<Integer> cycle;

    public Cycle(GraphLL graph) {
        cycle = new LinkedList<>();
        marked = new boolean[graph.numOfVert()];
        edgeTo = new int[graph.numOfVert()];

        if(hasSelfLoop(graph)) {
            return;
        }

        if(hasParallelEdges(graph)) {
            return;
        }
        for(int vertex = 0; vertex < graph.numOfVert(); vertex++) {
            if(!marked[vertex]) {
                dfs(graph, -1, vertex);
            }
        }
    }


    /**********
     *methods
     */

    private void dfs(GraphLL graph, int u, int vertex) {
        marked[vertex] = true;
        for(int otherVertex: graph.adjVerts((vertex))) {
            if(!cycle.isEmpty()) {
                return;
            }

            if(!marked[otherVertex]){
                edgeTo[otherVertex] = vertex;
                dfs(graph, vertex, otherVertex);
            } else if(otherVertex != u) {
                for(int x = vertex; x != otherVertex; x = edgeTo[x]) {
                    cycle.addFirst(x);
                }
                cycle.addFirst(otherVertex);
                cycle.addFirst(vertex);
            }
        }
    }

    public boolean hasCycle() {
        return !cycle.isEmpty();
    }

    public Iterable<Integer> cycle() {
        return cycle;
    }

    private boolean hasSelfLoop(GraphLL graph) {
        for(int vertex = 0; vertex< graph.numOfVert(); vertex++) {
            for(int otherVertex: graph.adjVerts((vertex))) {
                if(vertex == otherVertex) {
                    cycle.addFirst(vertex);
                    cycle.addFirst(vertex);

                    return true;
                }
            }
        }
        return false;
    }

    private boolean hasParallelEdges(GraphLL graph) {
        for(int vertex = 0; vertex< graph.numOfVert(); vertex++) {
            for(int otherVertex: graph.adjVerts((vertex))) {
                if(marked[otherVertex]) {
                    cycle.addFirst(vertex);
                    cycle.addFirst(otherVertex);
                    cycle.addFirst(vertex);
                    return true;
                }
                marked[otherVertex] = true;
            }
            for(int otherVertex: graph.adjVerts(vertex)) {
                marked[otherVertex] = false;
            }
        }
        return false;
    }
}

public class DigraphCycle {
    private boolean[] marked;
    private int[] edgeTo;
    private boolean[] onStack;
    private LinkedList<Integer> cycle;

    public DigraphCycle(Digraph graph) {
        marked  = new boolean[graph.V()];
        onStack = new boolean[graph.V()];
        edgeTo  = new int[graph.V()];
        cycle = new LinkedList<Integer>();

        for (int v = 0; v < graph.V(); v++) {
            if (!marked[v] && cycle.size() == 0) {
                dfs(graph, v);
            }
        }
    }

    private void dfs(Digraph graph, int v) {
        onStack[v] = true;
        marked[v] = true;
        for (int w : graph.edgesOut(v)) {

            if (cycle.size() != 0) {
                // if a cycle has been detected already, stop looking.
                return;
            }
            // found new vertex, so
            else if (!marked[w]) {
                // a new vertex, recursivly recur downward
                edgeTo[w] = v;
                dfs(graph, w);
            }
            else if (onStack[w]) {
                // some other recursive call has been through this vertex
                // this must represent a cycle.
                for (int x = v; x != w; x = edgeTo[x]) {
                    cycle.addFirst(x);
                }
                cycle.addFirst(w);
                cycle.addFirst(v);
            }
        }
        onStack[v] = false;
    }

    public boolean hasCycle() {
        return cycle.size() > 0;
    }

    public Iterable<Integer> cycle() {
        return cycle;
    }

    public static void main(String[] args) {
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            String fName = "tinyDG.txt";
            Digraph graph = new Digraph(fName);

            DigraphCycle finder = new DigraphCycle(graph);
            if (finder.hasCycle()) {
                System.out.print(fName + " directed cycle: ");
                for (int v : finder.cycle()) {
                    System.out.print(v + " ");
                }
                System.out.println();
            } else {
                System.out.println(fName + " has no directed cycle");
            }
            System.out.println();
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            String fName = "tinyDAG1.txt";
            Digraph graph = new Digraph(fName);

            DigraphCycle finder = new DigraphCycle(graph);
            if (finder.hasCycle()) {
                System.out.print(fName + " directed cycle: ");
                for (int v : finder.cycle()) {
                    System.out.print(v + " ");
                }
                System.out.println();
            } else {
                System.out.println(fName + " has no directed cycle");
            }
            System.out.println();
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            String fName = "tinyDAG2.txt";
            Digraph graph = new Digraph(fName);

            DigraphCycle finder = new DigraphCycle(graph);
            if (finder.hasCycle()) {
                System.out.print(fName + " directed cycle: ");
                for (int v : finder.cycle()) {
                    System.out.print(v + " ");
                }
                System.out.println();
            } else {
                System.out.println(fName + " has no directed cycle");
            }
            System.out.println();
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
    }
}

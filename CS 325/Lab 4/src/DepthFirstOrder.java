public class DepthFirstOrder {
    private boolean[] marked;
    private int[] pre;                 // pre[v]    = preorder  number of v
    private int[] post;                // post[v]   = postorder number of v
    private Queue<Integer> preorder;   // vertices in preorder
    private Queue<Integer> postorder;  // vertices in postorder
    private int preCounter;            // counter for preorder numbering
    private int postCounter;           // counter for postorder numbering

    public DepthFirstOrder(Digraph graph) {
        pre    = new int[graph.V()];
        post   = new int[graph.V()];
        postorder = new Queue<Integer>();
        preorder  = new Queue<Integer>();
        marked    = new boolean[graph.V()];

        for (int v = 0; v < graph.V(); v++) {
            if (!marked[v])
                dfs(graph, v);
        }
    }

    private void dfs(Digraph graph, int v) {
        marked[v] = true;
        pre[v] = preCounter++;
        preorder.enqueue(v);

        for (int w : graph.edgesOut(v)) {
            if (!marked[w]) {
                dfs(graph, w);
            }
        }
        postorder.enqueue(v);
        post[v] = postCounter++;
    }

    public int pre(int v) {
        if (validVertex(v)) {
            return pre[v];
        }
        else {
            throw new IllegalArgumentException("pre: invalid vertex");
        }
    }

    public int post(int v) {
        if (validVertex(v)) {
            return post[v];
        }
        else {
            throw new IllegalArgumentException("post: invalid vertex");
        }
    }

    public Iterable<Integer> post() {
        return postorder;
    }

    public Iterable<Integer> pre() {
        return preorder;
    }

    public Iterable<Integer> reversePost() {
        Stack<Integer> reverse = new Stack<Integer>();

        for (int v : postorder) {
            reverse.push(v);
        }
        return reverse;
    }

    private boolean validVertex(int vert) {
        return (vert >= 0 && vert < marked.length);
    }

    public static void main(String[] args) {
        {
            String fName = "tinyDAG1.txt";
            Digraph graph = new Digraph(fName);
            DepthFirstOrder dfs = new DepthFirstOrder(graph);

            System.out.println("   v  pre post");
            System.out.println("--------------");
            for (int v = 0; v < graph.V(); v++) {
                System.out.printf("%4d %4d %4d\n", v, dfs.pre(v), dfs.post(v));
            }

            System.out.print("Preorder:  ");
            for (int v : dfs.pre()) {
                System.out.print(v + " ");
            }
            System.out.println();

            System.out.print("Postorder: ");
            for (int v : dfs.post()) {
                System.out.print(v + " ");
            }
            System.out.println();

            System.out.print("Reverse postorder: ");
            for (int v : dfs.reversePost()) {
                System.out.print(v + " ");
            }
            System.out.println();
        }
        {
            String fName = "Classes.txt";
            Digraph graph = new Digraph(fName);
            DepthFirstOrder dfs = new DepthFirstOrder(graph);

            System.out.println("   v  pre post");
            System.out.println("--------------");
            for (int v = 0; v < graph.V(); v++) {
                System.out.printf("%4d %4d %4d\n", v, dfs.pre(v), dfs.post(v));
            }

            System.out.print("Preorder:  ");
            for (int v : dfs.pre()) {
                System.out.print(v + " ");
            }
            System.out.println();

            System.out.print("Postorder: ");
            for (int v : dfs.post()) {
                System.out.print(v + " ");
            }
            System.out.println();

            System.out.print("Reverse postorder: ");
            for (int v : dfs.reversePost()) {
                System.out.print(v + " ");
            }
            System.out.println();
        }
    }
}

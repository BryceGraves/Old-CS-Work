import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Scanner;

public class Digraph {
    private final int numVert; // the number of vertices is fixed.
    private int numEdges;
    private LinkedList<Integer>[] edgesOut;
    //private LinkedList<Integer>[] edgesIn;
    private LinkedList<Integer> vertices;
    private int[] inDegree;

    public Digraph(int v) {
        numVert = v;
        numEdges = 0;
        inDegree = new int[numVert];
        edgesOut = (LinkedList<Integer>[]) new LinkedList[numVert];
        vertices = new LinkedList<Integer>();
        for(int i = 0; i < this.numVert; i++) {
            edgesOut[i] = new LinkedList<Integer>();
            vertices.addLast(i);
        }
    }

    public Digraph(String inFileName) {
        Scanner scanner = null;
        try {
            File inFile = new File(inFileName);
            FileInputStream fis = new FileInputStream(inFile);
            scanner = new Scanner(new BufferedInputStream(fis));
        }
        catch (IOException ioe) {
            throw new IllegalArgumentException(ioe.getMessage());
        }
        try {
            numVert = scanner.nextInt();
            int e = scanner.nextInt();
            numEdges = 0;
            inDegree = new int[numVert];
            edgesOut = (LinkedList<Integer>[]) new LinkedList[this.numVert];
            vertices = new LinkedList<Integer>();
            for (int i = 0; i < this.numVert; i++) {
                edgesOut[i] = new LinkedList<Integer>();
                vertices.addLast(i);
            }
            for (int i = 0; i < e; i++) {
                int v = scanner.nextInt();
                int w = scanner.nextInt();
                addEdge(v, w);
            }
            // I'm assuming that when I close the scanner, the File will get
            // closed and deallocated too.
            scanner.close();
        }
        catch (NullPointerException e) {
            throw new NullPointerException("Dude, null pointers not allowed!");
        }
    }

    public void addEdge(int from, int to) {
        // De Morgan's laws
        //    the negation of a disjunction is the conjunction of the negations; and
        //    the negation of a conjunction is the disjunction of the negations;
        //
        //    not (A or B) = not A and not B; and
        //    not (A and B) = not A or not B
        if (!validVertex(from) || !validVertex(to)) {
            throw new IllegalArgumentException("addEdge: invalid vertex");
        }
        edgesOut[from].addFirst(to);
        inDegree[to]++;
        numEdges++;
    }

    public int V() { return numVert; }

    public int E() { return numEdges; }

    public boolean hasEdge(int from, int to) {
        for (Integer edge : edgesOut(from)) {
            if (edge == to) { return true; }
        }
        return false;
    }

    public Digraph reverse() {
        Digraph newGraph = new Digraph(numVert);

        for (Integer vert : verts()) {
            for (Integer edge : edgesOut(vert)) {
                newGraph.addEdge(edge, vert);
            }
        }

        return newGraph;
    }

    public Iterable<Integer> verts() { return vertices; }

    private boolean validVertex(int vert) {
        return (vert >= 0 && vert < numVert);
    }

    // the list of all outgoing edges
    public Iterable<Integer> edgesOut(int v) {
        if (!validVertex(v))
            throw new IllegalArgumentException("adjVerts: invalid vertex");
        return edgesOut[v];
    }

    public int outDegree(int v) {
        validVertex(v);
        return edgesOut[v].size();
    }

    public int inDegree(int v) {
        validVertex(v);
        return inDegree[v];
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append("Vertices: " + numVert + "   Edges: " + numEdges + "\n");
        for (int v = 0; v < numVert; v++) {
            s.append("\tvertex: " + v + " -> ");
            for (int w : edgesOut[v]) {
                s.append(w + " ");
            }
            s.append("\n");
        }
        return s.toString();
    }

    public static void main(String[] args) {
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            Digraph g = new Digraph(2);
            g.addEdge(0, 1);
            System.out.println(g.toString());

            assert g.V() == 2;
            assert g.E() == 1;

            assert g.outDegree(0) == 1;
            assert g.inDegree(0) == 0;
            assert g.outDegree(1) == 0;
            assert g.inDegree(1) == 1;

            // Since we are within the class, we can call private methods.
            assert g.validVertex(0) == true;
            assert g.validVertex(2) == false;
            assert g.validVertex(-1) == false;
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            Digraph g = new Digraph(15);

            g.addEdge(0, 1);
            g.addEdge(0, 2);
            g.addEdge(0, 3);
            g.addEdge(0, 4);
            g.addEdge(0, 5);
            g.addEdge(1, 7);
            g.addEdge(2, 7);
            g.addEdge(5, 5);
            g.addEdge(5, 9);
            g.addEdge(7, 5);

            assert g.hasEdge(0, 1);
            assert g.hasEdge(0, 2);
            assert g.hasEdge(7, 5);


            assert g.V() == 15;
            // Since we are within the class, we can call private members.
            assert g.V() == g.numVert;
            assert g.V() == g.edgesOut.length;
            assert g.E() == 10;
            assert g.E() == g.numEdges;

            assert g.outDegree(0) == 5;
            assert g.inDegree(0) == 0;
            assert g.outDegree(5) == 2;
            assert g.inDegree(5) == 3;
            assert g.outDegree(7) == 1;
            assert g.inDegree(7) == 2;

            g = g.reverse();
            assert g.hasEdge(1, 0);
            assert g.hasEdge(2, 0);
            assert g.hasEdge(5, 7);

            {
                //Integer[] test = {1, 2, 3, 4, 5};
                Integer[] test = {5, 4, 3, 2, 1};
                int i = 0;
                for (int j : g.edgesOut(0)) {
                    assert test[i++] == j;
                }
            }
            {
                for (int v = 0; v < g.V() ; v++) {
                    System.out.println("vert: " + v);
                }
                for (int v : g.verts()) {
                    System.out.println("vert: " + v);
                }
            }
            System.out.println(g.toString());
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            Digraph g = new Digraph("tinyG.txt");

            System.out.println(g.toString());
            assert g.V() == 13;
            assert g.E() == 13;
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            Digraph g = new Digraph("tinyCG.txt");

            System.out.println(g.toString());
            assert g.V() == 6;
            assert g.E() == 8;

            assert g.outDegree(0) == 3;
            assert g.inDegree(0) == 0;
            assert g.outDegree(2) == 2;
            assert g.inDegree(2) == 2;
            assert g.outDegree(3) == 2;
            assert g.inDegree(3) == 1;
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            Digraph g = new Digraph("tinyDG.txt");

            System.out.println(g.toString());
            assert g.V() == 13;
            assert g.E() == 22;

            assert g.outDegree(0) == 2;
            assert g.inDegree(0) == 2;
            assert g.outDegree(6) == 4;
            assert g.inDegree(6) == 2;
            assert g.outDegree(12) == 1;
            assert g.inDegree(12) == 2;
            {
                Integer[] test = {9, 4, 8, 0};
                int i = 0;
                for (int j : g.edgesOut(6)) {
                    assert test[i++] == j;
                }
            }
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            Digraph g = new Digraph("Classes.txt");

            System.out.println(g.toString());
            assert g.V() == 7;
            assert g.E() == 11;

            assert g.outDegree(0) == 3;
            assert g.inDegree(0) == 1;
            assert g.outDegree(6) == 2;
            assert g.inDegree(6) == 1;
            assert g.outDegree(3) == 4;
            assert g.inDegree(3) == 0;
            {
                Integer[] test = {2, 4, 5, 6};
                int i = 0;
                for (int j : g.edgesOut(3)) {
                    assert test[i++] == j;
                }
            }
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
    }
}

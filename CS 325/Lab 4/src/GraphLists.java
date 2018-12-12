import java.io.*;
import java.util.Scanner;

public class GraphLists {
    private final int numVert; // the number of vertices is fixed.
    private int numEdges;
    private LinkedList<Integer>[] adjLists;

    public GraphLists(int v) {
        if (v < 0)
            throw new IllegalArgumentException("GraphLists: Number of vertices must be geq 0");
        this.numVert = v;
        numEdges = 0;
        adjLists = (LinkedList<Integer>[]) new LinkedList[this.numVert];
        for(int i = 0; i < this.numVert; i++) {
            adjLists[i] = new LinkedList<Integer>();
        }
    }

    public GraphLists(String inFileName) {
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
            adjLists = (LinkedList<Integer>[]) new LinkedList[this.numVert];
            for (int i = 0; i < this.numVert; i++) {
                adjLists[i] = new LinkedList<Integer>();
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

    public int V() { return numVert; }

    public int E() { return numEdges; }

    private boolean validVertex(int vert) {
        return (vert >= 0 && vert < numVert);
    }

    public void addEdge(int v, int w) {
        if (!validVertex(v) || !validVertex(w))
            throw new IllegalArgumentException("addEdge: invalid vertex");
        if (hasEdge(v, w) || v == w) return;

        adjLists[v].addLast(w);
        adjLists[w].addLast(v);
        numEdges++;
    }

    public int degree(int v) {
        if (!validVertex(v))
            throw new IllegalArgumentException("degree: invalid vertex");
        return adjLists[v].size();
    }

    public Iterable<Integer> adjVerts(int v) {
        if (!validVertex(v))
            throw new IllegalArgumentException("adjVerts: invalid vertex");
        return adjLists[v];
    }

    public boolean hasEdge(int from, int to) {
        for (Integer vert : adjVerts(from)) {
            if (vert == to) { return true; }
        }
        return false;
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append("Vertices: " + numVert + "   Edges: " + numEdges + "\n");
        for (int v = 0; v < numVert; v++) {
            s.append("\tvertex: " + v + " -> ");
            for (int w : adjLists[v]) {
                s.append(w + " ");
            }
            s.append("\n");
        }
        return s.toString();
    }

    public static void main(String[] args) {
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            GraphLists g = new GraphLists(2);
            g.addEdge(0,1);
            System.out.println(g.toString());

            assert g.V() == 2;
            assert g.E() == 1;
            assert g.degree(0) == 1;
            assert g.degree(1) == 1;

            // Since we are within the class, we can call private methods.
            assert g.validVertex(0) == true;
            assert g.validVertex(2) == false;
            assert g.validVertex(-1) == false;
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            GraphLists g = new GraphLists(15);

            g.addEdge(0, 1);
            g.addEdge(0, 2);
            g.addEdge(0, 3);
            g.addEdge(0, 4);
            g.addEdge(0, 5);
            g.addEdge(0, 5);
            g.addEdge(1, 7);
            g.addEdge(2, 7);
            g.addEdge(5, 5);
            g.addEdge(5, 9);
            g.addEdge(7, 5);

            assert g.hasEdge(0, 1);
            assert g.hasEdge(0, 2);
            assert g.hasEdge(0, 3);
            assert g.hasEdge(0, 4);
            assert g.hasEdge(5, 7);

            assert g.V() == 15;
            // Since we are within the class, we can call private members.
            assert g.V() == g.numVert;
            assert g.V() == g.adjLists.length;
            System.out.println(g.E());
            //assert g.E() == 10; //I added a new check for non-dup and non-parallel
            assert g.E() == 9;

            assert g.E() == g.numEdges;

            assert g.degree(0) == 5;
            assert g.degree(0) == g.adjLists[0].size();
            assert g.degree(1) == 2;
            assert g.degree(1) == g.adjLists[1].size();
            assert g.degree(7) == 3;
            assert g.degree(7) == g.adjLists[7].size();
            assert g.degree(8) == 0;
            assert g.degree(8) == g.adjLists[8].size();

            System.out.println("Vertex count: " + g.V());
            System.out.println("Edge count: " + g.E());
            System.out.println("Degree " + 0 + ": " + g.degree(0));
            System.out.println("Degree " + 5 + ": " + g.degree(5));
            System.out.println("Degree " + 7 + ": " + g.degree(7));

            System.out.print("Vertices adjacent to " + 0 + ":  ");
            for (int i : g.adjVerts(0)) {
                System.out.print(i + "  ");
            }
            System.out.println();

            System.out.print("Vertices adjacent to " + 7 + ":  ");
            for (int i : g.adjVerts(7)) {
                System.out.print(i + "  ");
            }
            System.out.println();
            System.out.println(g.toString());

            {
                Integer[] test = {1, 2, 3, 4, 5};
                int i = 0;
                for (int j : g.adjVerts(0)) {
                    assert test[i++] == j;
                }
            }
            {
                Integer[] test = {1, 2, 5};
                int i = 0;
                for (int j : g.adjVerts(7)) {
                    assert test[i++] == j;
                }
            }
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
        {
            // Yep, I should create a truckload of tests for this.
            GraphLists g = new GraphLists("tinyG.txt");
            System.out.println(g.toString());
        }
        System.out.println("+++++++++++++++++++++++++++++++++++++");
    }
}

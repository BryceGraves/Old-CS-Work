import java.util.LinkedList;
public class four {
    public static void main(String[] args) {
        LinkedList<NumberAndColor> numberAndColor = new LinkedList<>();
        numberAndColor.add(new NumberAndColor(1, "orange"));
        numberAndColor.add(new NumberAndColor(2, "green"));
        numberAndColor.add(new NumberAndColor(3, "orange"));
        numberAndColor.add(new NumberAndColor(4, "purple"));
        numberAndColor.add(new NumberAndColor(5, "green"));
        numberAndColor.add(new NumberAndColor(6, "purple"));
        numberAndColor.add(new NumberAndColor(7, "orange"));


//        numberAndColor.add(new NumberAndColor(1, "purple"));
//        numberAndColor.add(new NumberAndColor(2, "purple"));
//        numberAndColor.add(new NumberAndColor(3, "purple"));
//        numberAndColor.add(new NumberAndColor(4, "green"));
//        numberAndColor.add(new NumberAndColor(5, "orange"));
//        numberAndColor.add(new NumberAndColor(6, "orange"));
//        numberAndColor.add(new NumberAndColor(7, "green"));

        LinkedList<NumberAndColor> theReturnedReturnBoat =  ColorSort.sort(numberAndColor);

        for (NumberAndColor item : theReturnedReturnBoat) {
            StdOut.print("(" + item.number + ", " + item.color + "), ");
        }
    }
}

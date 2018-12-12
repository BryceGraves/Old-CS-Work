import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;


public class ColorSort {
    public static LinkedList<NumberAndColor> sort (LinkedList<NumberAndColor> input) {
        Map<String, LinkedList<NumberAndColor>> colors = new HashMap<>();
        LinkedList<NumberAndColor> returnBoat = new LinkedList<>();
        for (NumberAndColor current : input) {
            if (!colors.containsKey(current.color)) {
                colors.put(current.color, new LinkedList<>());
            }
            colors.get(current.color).addLast(current);
        }

        for (LinkedList<NumberAndColor> list : colors.values()) {
            returnBoat.addAll(list);
        }

        return returnBoat;
    }
}

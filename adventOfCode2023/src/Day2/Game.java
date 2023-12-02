package Day2;

import java.util.*;

public class Game {
    private final int id;
    private List<List<Subset>> subsets;
    private static Map<Color, Integer> colorQuantity = new HashMap<>();

    private record Subset(Color color, int quantity) {
        public String toString() {
                return this.quantity + " " + this.color;
            }
        }

    public Game(int id) {
        this.id = id;
        this.subsets = new ArrayList<>();
    }

    public void addSubset(Color color, int quantity, int index) {
        Subset subset = new Subset(color, quantity);
        List<Subset> subsets;
        try {
            subsets = this.subsets.get(index);
        } catch (IndexOutOfBoundsException e) {
            subsets = new ArrayList<>();
            this.subsets.add(index, subsets);
        }
        subsets.add(subset);
    }

    public static void addColorQuantity(Color color, int quantity) {
        colorQuantity.put(color, quantity);
    }

    public boolean isValid() {
        for (List<Subset> subsets : this.subsets) {
            for (Subset subset : subsets) {
                int availableQuantity = colorQuantity.get(subset.color);
                if (subset.quantity > availableQuantity) {
                    return false;
                }
            }
        }
        return true;
    }

    public Map<Color, Integer> getMinimumSet() {
        Map<Color, Integer> maxQuantity = new HashMap<>();
        for (List<Subset> subsets : this.subsets) {
            for (Subset subset : subsets) {
                if (maxQuantity.containsKey(subset.color)) {
                    int currentMax = maxQuantity.get(subset.color);
                    if (subset.quantity > currentMax) {
                        maxQuantity.put(subset.color, subset.quantity);
                    }
                } else {
                    maxQuantity.put(subset.color, subset.quantity);
                }
            }
        }
        return maxQuantity;
    }

    public int getId() {
        return this.id;
    }

    public String toString() {
        StringBuilder subsets = new StringBuilder();
        for (List<Subset> subset : this.subsets) {
            subsets.append("\t").append(subset.toString()).append("\n");
        }
        return "Game " + this.id + ":\n" + subsets;
    }
}

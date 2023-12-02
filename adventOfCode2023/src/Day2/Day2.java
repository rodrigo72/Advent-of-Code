package Day2;

import aoc.Base;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Day2 extends Base<List<Game>> {
    public void generator() {
        this.processed = new ArrayList<>();
        int id = 1;

        for (String line : this.input.split("\n")) {
            Game game = new Game(id++);
            String[] parts = line.split(":");
            String[] parts2 = parts[1].split(";");

            int index = 0;
            for (String subsets : parts2) {
                String[] parts3 = subsets.split(",");

                for (String subset : parts3) {
                    String[] parts4 = subset.split(" ");
                    try {
                        int quantity = Integer.parseInt(parts4[1]);
                        Color color = Color.parseColor(parts4[2]);
                        game.addSubset(color, quantity, index);
                    } catch (NumberFormatException  e) {
                        System.out.println("Error parsing number");
                    }
                }
                index++;
            }
            this.processed.add(game);
        }
    }

    public void part1() {
        Game.addColorQuantity(Color.red, 12);
        Game.addColorQuantity(Color.green, 13);
        Game.addColorQuantity(Color.blue, 14);

        int sumValidIds = 0;
        for (Game game : this.processed)
            if (game.isValid())
                sumValidIds += game.getId();

        System.out.println("Sum of valid ids: " + sumValidIds);
    }

    public void part2() {
        int totalSum = 0;
        for (Game game : this.processed) {
            int sum = game.getMinimumSet().values()
                    .stream().reduce(1, (a, b) -> a * b);
            totalSum += sum;
        }
        System.out.println("Total sum: " + totalSum);
    }
}

package Day4;

import aoc.Base;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public class Day4 extends Base<List<Card>> {
    public void generator() {
        this.processed = new ArrayList<>();

        for (String line : this.input.split("\n")) {
            String[] parts = line.split("[:|]");
            Card card = new Card();

            for (int i = 1; i < 3; i++)
                try {
                    Set<Integer> numbers = Arrays.stream(parts[i].split(" "))
                            .filter(s -> !s.equals("") && !s.equals(" "))
                            .map(Integer::parseInt)
                            .collect(Collectors.toSet());
                    if (i == 1) card.setWinningNumbers(numbers);
                    else card.setNumbers(numbers);
                } catch (NumberFormatException e) {
                    System.out.println("Error parsing number");
                }

            this.processed.add(card);
        }
    }

    public void part1() {
        System.out.println("Total points: " +
                this.processed.stream()
                        .map(Card::getPoints)
                        .reduce(0.0, Double::sum));
        Card.resetId();
    }

    public void part2() {
        for (Card card : this.processed) {
            Set<Integer> commonNumbers = card.getCommonNumbers();
            for (int i = card.getId(); i < card.getId() + commonNumbers.size(); i++)
                if (i < this.processed.size())
                    this.processed.get(i).incrementInstances(card.getInstances());

        }

        System.out.println("Total instances: " +
                this.processed.stream()
                        .map(Card::getInstances)
                        .reduce(0, Integer::sum));
    }
}

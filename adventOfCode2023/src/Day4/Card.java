package Day4;

import java.util.Set;
import java.util.stream.Collectors;

public class Card {
    private static int incId = 1;
    private final int id;
    private Set<Integer> numbers;
    private Set<Integer> winningNumbers;

    private int instances;
    public Card() {
        this.id = incId;
        incId += 1;
        this.instances = 1;
    }

    public static void resetId() {
        incId = 1;
    }

    public void incrementInstances(int value) {
        this.instances += value;
    }

    public int getInstances() {
        return this.instances;
    }

    public Set<Integer> getCommonNumbers() {
        return this.numbers.stream()
                .filter(this.winningNumbers::contains)
                .collect(Collectors.toSet());
    }

    public double getPoints() {
        int commonNumbers = (int) this.numbers.stream()
                .filter(this.winningNumbers::contains)
                .count();
        if (commonNumbers == 0) return 0;
        return Math.pow(2, commonNumbers - 1);
    }

    public int getId() {
        return id;
    }

    public void setNumbers(Set<Integer> numbers) {
        this.numbers = numbers;
    }

    public void setWinningNumbers(Set<Integer> winningNumbers) {
        this.winningNumbers = winningNumbers;
    }

}

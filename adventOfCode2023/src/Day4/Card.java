package Day4;

import java.util.Set;

public class Card {
    private static int incId = 1;
    private final int id;
    private Set<Integer> numbers, winningNumbers;
    private int instances;

    public Card() {
        this.id = incId;
        incId += 1;
        this.instances = 1;
    }

    public int getCommonNumbersSize() {
        return (int) this.numbers.stream()
                .filter(this.winningNumbers::contains)
                .count();
    }

    public double getPoints() {
        int commonNumbers = this.getCommonNumbersSize();
        if (commonNumbers == 0) return 0;
        return Math.pow(2, commonNumbers - 1);
    }

    public static void resetId() { incId = 1; }
    public void incrementInstances(int value) { this.instances += value; }
    public int getInstances() { return this.instances; }
    public int getId() { return id; }
    public void setNumbers(Set<Integer> numbers) { this.numbers = numbers; }
    public void setWinningNumbers(Set<Integer> winningNumbers) { this.winningNumbers = winningNumbers; }
}

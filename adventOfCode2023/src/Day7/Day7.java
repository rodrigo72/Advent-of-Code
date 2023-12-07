package Day7;

import aoc.Base;

import java.util.ArrayList;
import java.util.List;

public class Day7 extends Base<List<Hand>>{
    @Override
    public void generator() {
        this.processed = new ArrayList<>();
        for (String line : this.input.split("\n")) {
            String[] hand = line.split(" ");
            this.processed.add(new Hand(hand[0], Integer.parseInt(hand[1])));
        }
    }

    public void aux() {
        int rank = 1, sum = 0;
        this.processed.sort(Hand::compareTo);

        for (Hand hand : this.processed) {
            sum += hand.getBid() * rank;
            rank += 1;
        }

        System.out.println("Total winnings: " + sum);
    }

    @Override
    public void part1() {
        for (Hand hand : this.processed)
            hand.setType();
        this.aux();
    }

    @Override
    public void part2() {
        for (Hand hand : this.processed)
            hand.setType2();
        this.aux();
    }
}

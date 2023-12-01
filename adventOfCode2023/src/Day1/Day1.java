package Day1;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import aoc.Base;

public class Day1 extends Base<ArrayList<Integer>> {
    private record Result (boolean isDigit, int value, int offset) {}
    private final Map<String, Integer> spelledNumberMap;

    public Day1() {
        this.spelledNumberMap = new HashMap<>();
        spelledNumberMap.put("one", 1);
        spelledNumberMap.put("two", 2);
        spelledNumberMap.put("three", 3);
        spelledNumberMap.put("four", 4);
        spelledNumberMap.put("five", 5);
        spelledNumberMap.put("six", 6);
        spelledNumberMap.put("seven", 7);
        spelledNumberMap.put("eight", 8);
        spelledNumberMap.put("nine", 9);
    }

    private Result checkSpelledNumber(int o, String input) {


        for (Map.Entry<String, Integer> entry : spelledNumberMap.entrySet()) {
            String word = entry.getKey();
            int value = entry.getValue();

            if (input.regionMatches(o, word, 0, word.length()))
                return new Result(true, value, o + word.length());
        }
        return new Result(false, -1, -1);
    }

    public void generator() {

        this.processed = new ArrayList<>();
        for (String line : this.input.split("\n")) {
            int first = -1, last = -1, i = 0;
            for (; i < line.length(); i++) {
                char c = line.charAt(i);
                if (Character.isDigit(c)) {
                    int digit = c - '0';
                    if (first == -1)
                        first = digit;
                    last = digit;
                } else {
                    Result result = checkSpelledNumber(i, line);
                    if (result.isDigit()) {
                        if (first == -1)
                            first = result.value();
                        last = result.value();
                        i = result.offset() - 1;
                    }
                }
            }
            if (last == -1 && first != -1) last = first;
            if (first != -1) {
                String str = String.valueOf(first) + last;
                this.processed.add(Integer.parseInt(str));
            }
        }
    }

    public void part1() {
        int sum = 0;
        for (Integer s : this.processed) {
            sum += s;
        }
        System.out.println(sum);
    }

    public void part2() {
        this.part1();
    }
}

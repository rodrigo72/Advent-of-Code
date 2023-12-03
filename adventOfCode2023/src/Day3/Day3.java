package Day3;
import aoc.Base;
import java.util.*;

public class Day3 extends Base<Integer> {
    private record Coordinates(int x, int y) {}

    public Set<Coordinates> checkAround(String[] lines, int x, int y, int width, int height) {

        Set<Coordinates> coords = new HashSet<>();
        Set<Coordinates> coordsNumber = new HashSet<>();

        if (y != 0)      coords.add(new Coordinates(x, y + 1));
        if (y != height) coords.add(new Coordinates(x, y - 1));

        if (x - 1 >= 0) {
            coords.add(new Coordinates(x - 1, y));
            if (y != 0)      coords.add(new Coordinates(x - 1, y + 1));
            if (y != height) coords.add(new Coordinates(x - 1, y - 1));

        }
        if (x + 1 <= width) {
            coords.add(new Coordinates(x + 1, y));
            if (y != 0)      coords.add(new Coordinates(x + 1, y + 1));
            if (y != height) coords.add(new Coordinates(x + 1, y - 1));
        }

        for (Coordinates c : coords)
            if (Character.isDigit(lines[c.y].charAt(c.x)))
                coordsNumber.add(c);

        return coordsNumber;
    }

    public int getNumber(String[] lines, Coordinates c, int width, int height, Map<Coordinates, Integer> map) {

        List<Coordinates> coords = new ArrayList<>();
        String number = String.valueOf(lines[c.y].charAt(c.x));
        coords.add(new Coordinates(c.x, c.y));

        StringBuilder left = new StringBuilder();
        StringBuilder right = new StringBuilder();

        int i = 1;
        while (c.x + i <= width) {
            if (Character.isDigit(lines[c.y].charAt(c.x + i))) {
                right.append(lines[c.y].charAt(c.x + i));
                coords.add(new Coordinates(c.x + i, c.y));
                i++;
            } else {
                break;
            }
        }

        i = 1;
        while (c.x - i >= 0) {
            if (Character.isDigit(lines[c.y].charAt(c.x - i))) {
                left.append(lines[c.y].charAt(c.x - i));
                coords.add(new Coordinates(c.x - i, c.y));
                i++;
            } else {
                break;
            }
        }

        number = left.reverse() + number + right;
        int n = Integer.parseInt(number);

        for (Coordinates coordinates : coords)
            map.put(coordinates, n);

        return n;
    }

    public void generator() {}

    public void part1() {
        Map<Coordinates, Integer> numbers = new HashMap<>();
        String[] lines = this.input.split("\n");
        int height = lines.length - 1, sum = 0;

        for (int j = 0; j <= height; j++) {
            String line = lines[j];
            int width = line.length() - 1;

            for (int i = 0; i <= width; i++) {
                if (line.charAt(i) != '.'
                        && !Character.isDigit(line.charAt(i))) {
                    Set<Coordinates> coords = this.checkAround(lines, i, j, width, height);
                    for (Coordinates c : coords) {
                        if (!numbers.containsKey(c)) {
                            int n = this.getNumber(lines, c, width, height, numbers);
                            sum += n;
                        }
                    }
                }
            }
        }
        System.out.println(sum);
    }

    public void part2() {
        Map<Coordinates, Integer> numbers = new HashMap<>();
        String[] lines = this.input.split("\n");
        int height = lines.length - 1, sum = 0;

        for (int j = 0; j <= height; j++) {
            String line = lines[j];
            int width = line.length() - 1;

            for (int i = 0; i <= width; i++)
                if (line.charAt(i) == '*') {
                    Set<Coordinates> coords = this.checkAround(lines, i, j, width, height);
                    Set<Integer> numbersAround = new HashSet<>();
                    for (Coordinates c : coords) {
                        if (!numbers.containsKey(c)) {
                            int n = this.getNumber(lines, c, width, height, numbers);
                            numbersAround.add(n);
                        } else { numbersAround.add(numbers.get(c)); }
                    }
                    if (numbersAround.size() == 2)
                        sum += numbersAround.stream().reduce(1, (a, b) -> a * b);
                }
        }
        System.out.println(sum);
    }
}
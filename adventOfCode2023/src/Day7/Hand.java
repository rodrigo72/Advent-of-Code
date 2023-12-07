package Day7;

import java.util.*;

public class Hand implements Comparable<Hand> {
    private final String hand;
    private final int bid;
    private HandType type;

    public Hand(String hand, int bid) {
        this.hand = hand;
        this.bid = bid;
    }

    public HandType getType() {
        return this.type;
    }

    public void setType() {
        Map<Character, Integer> map = new HashMap<>();
        for (Character c : this.hand.toCharArray()) {
            map.put(c, map.getOrDefault(c, 0) + 1);
        }

        Map<Integer, Integer> map2 = new HashMap<>();
        for (Integer i : map.values()) {
            map2.put(i, map2.getOrDefault(i, 0) + 1);
        }

        this.setTypeAux(map2);
    }

    public void setType2() {
        Map<Character, Integer> map = new HashMap<>();
        for (Character c : this.hand.toCharArray()) {
            map.put(c, map.getOrDefault(c, 0) + 1);
        }

        int jokerCount = map.getOrDefault('J', 0);

        if (jokerCount == 5) {
            this.type = HandType.FIVE_OF_A_KIND;
            return;
        }

        map.remove('J');

        Map<Integer, Integer> map2 = new HashMap<>();
        for (Integer i : map.values()) {
            map2.put(i, map2.getOrDefault(i, 0) + 1);
        }

        if (jokerCount != 0) {
            List<Integer> list = new ArrayList<>(map2.keySet());
            list.sort(Collections.reverseOrder());
            for (Integer i : list) {
                if (i + jokerCount <= 5) {
                    map2.put(i + jokerCount, map2.getOrDefault(i + jokerCount, 0) + 1);
                    map2.put(i, map2.get(i) - 1);
                    break;
                }
            }
        }

        this.setTypeAux(map2);
    }

    private void setTypeAux(Map<Integer, Integer> map2) {
        if (map2.getOrDefault(5, 0) == 1) {
            this.type = HandType.FIVE_OF_A_KIND;
        } else if (map2.getOrDefault(4, 0) == 1) {
            this.type = HandType.FOUR_OF_A_KIND;
        } else if (map2.getOrDefault(3, 0) == 1 && map2.getOrDefault(2, 0) == 1) {
            this.type = HandType.FULL_HOUSE;
        } else if (map2.getOrDefault(3, 0) == 1) {
            this.type = HandType.THREE_OF_A_KIND;
        } else if (map2.getOrDefault(2, 0) == 2) {
            this.type = HandType.TWO_PAIR;
        } else if (map2.getOrDefault(2, 0) == 1) {
            this.type = HandType.ONE_PAIR;
        } else this.type = HandType.HIGH_CARD;
    }

    @Override
    public int compareTo(Hand o) {
        if (this.type.getValue() != o.getType().getValue())
            return o.getType().getValue() - this.type.getValue();

        if (this.hand.length() != o.hand.length())
            throw new IllegalArgumentException("Hands have different lengths");

        for (int i = 0; i < this.hand.length(); i++) {
            int result = Integer.compare(
                    CardType.getValue(this.hand.charAt(i)),
                    CardType.getValue(o.getHand().charAt(i))
            );
            if (result != 0) return result;
        }

        return 0;
    }


    public String getHand() {
        return this.hand;
    }

    public int getBid() {
        return this.bid;
    }

    public String toString() {
        return this.hand + " " + this.bid + " " + this.type;
    }
}

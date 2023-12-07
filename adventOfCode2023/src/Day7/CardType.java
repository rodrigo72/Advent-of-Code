package Day7;

public enum CardType {
    TWO(1),
    THREE(2),
    FOUR(3),
    FIVE(4),
    SIX(5),
    SEVEN(6),
    EIGHT(7),
    NINE(8),
    TEN(9),
    JACK(0),
    QUEEN(11),
    KING(12),
    ACE(13);

    private final int value;

    CardType(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }

    public static int getValue(char c) {
        return switch (c) {
            case '2' -> TWO.getValue();
            case '3' -> THREE.getValue();
            case '4' -> FOUR.getValue();
            case '5' -> FIVE.getValue();
            case '6' -> SIX.getValue();
            case '7' -> SEVEN.getValue();
            case '8' -> EIGHT.getValue();
            case '9' -> NINE.getValue();
            case 'T' -> TEN.getValue();
            case 'J' -> JACK.getValue();
            case 'Q' -> QUEEN.getValue();
            case 'K' -> KING.getValue();
            case 'A' -> ACE.getValue();
            default -> -1;
        };
    }
}

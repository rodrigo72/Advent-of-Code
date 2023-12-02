package Day2;

public enum Color {
    blue,
    red,
    green;

    public static Color parseColor(String color) {
        return switch (color) {
            case "blue" -> Color.blue;
            case "red" -> Color.red;
            case "green" -> Color.green;
            default -> null;
        };
    }
}

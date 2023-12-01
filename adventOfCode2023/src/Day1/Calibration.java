package Day1;

public record Calibration(int first, int last) {
    public String toString() {
        return String.format("(%d, %d)", this.first, this.last);
    }

    public int sum() {
        return this.first + this.last;
    }
}

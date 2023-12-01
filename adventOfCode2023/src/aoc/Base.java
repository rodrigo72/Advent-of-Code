package aoc;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;


abstract public class Base<T> {
    private String className;
    protected String input;
    protected T processed;

    public void run(boolean verbose){
        long startTime = System.nanoTime();
        this.className = this.getClass().getSimpleName();
        System.out.println(this.className);

        getInput();
        long time_input = System.nanoTime();
        generator();
        long time_generator = System.nanoTime();
        part1();
        long time_part1 = System.nanoTime();
        generator();
        long time_generator2 = System.nanoTime();
        part2();
        long time_part2 = System.nanoTime();

        if(verbose){
            System.out.printf(
                    """
                    Time durations (µs):
                        Generator:  %7d
                        Part 1:     %7d
                        Part 2:     %7d
                        Total:      %7d
                    """,
                    (time_generator - time_input)/1000,
                    (time_part1 - time_generator)/1000,
                    (time_part2 - time_generator2)/1000,
                    (time_part2 - startTime)/1000
            );
        }

        System.out.println();
    }

    void getInput() {
        String path = String.format("./input/%s.txt", this.className);

        StringBuilder contentBuilder = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new FileReader(path))) {
            String sCurrentLine;
            while ((sCurrentLine = reader.readLine()) != null) {
                contentBuilder.append(sCurrentLine).append("\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        this.input = contentBuilder.toString();
    }

    public abstract void generator();

    public abstract void part1();

    public abstract void part2();
}

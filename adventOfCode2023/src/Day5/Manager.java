package Day5;

import java.util.*;

public class Manager {
    public record Range(long start, long end, long size) implements Comparable<Range> {
        @Override
        public int compareTo(Range o) {
            return Long.compare(this.end, o.end);
        }
    }
    public record SeedRange(long start, long size) {}
    List<List<Range>> lists;
    Set<Long> seeds;
    List<SeedRange> seedRanges;

    public Manager(List<Long> seedsList) {
        this.seeds = new HashSet<>(seedsList);
        this.seedRanges = new ArrayList<>();

        for (int i = 0; i < seedsList.size(); i += 2) {
            this.seedRanges.add(new SeedRange(
                    seedsList.get(i),
                    seedsList.get(i+1)
            ));
        }

        this.lists = new ArrayList<>(6);
        for (int i = 0; i < 7; i++) {
            this.lists.add(new ArrayList<>() {
                    public boolean add(Range mt) {
                        int index = Collections.binarySearch(this, mt);
                        if (index < 0) index = ~index;
                        super.add(index, mt);
                        return true;
                    }
                }
            );
        }
    }

    public void addRange(long start, long end, long size, int index) {
        this.lists.get(index).add(new Range(start, end, size));
    }

    public List<List<Range>> getLists() {
        return this.lists;
    }

    public Set<Long> getSeeds() {
        return this.seeds;
    }

    public boolean checkSeedRanges(long value) {
        for (SeedRange range : this.seedRanges) {
            if (value >= range.start() && value < range.start() + range.size())
                return true;
        }
        return false;
    }

}
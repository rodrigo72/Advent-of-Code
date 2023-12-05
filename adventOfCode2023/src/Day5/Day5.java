package Day5;

import aoc.Base;

import java.util.*;
import java.util.concurrent.*;
import Day5.Manager.Range;

public class Day5 extends Base<Manager> {
    public void generator() {
        String[] lines = this.input.split("\n");
        List<Long> seeds = Arrays.stream(lines[0].split(":")[1].split(" "))
                .filter(s -> !s.equals(""))
                .map(Long::parseLong)
                .toList();

        int count = 0;
        this.processed = new Manager(seeds);

        for (int i = 1; i < lines.length; i++) {
            if (!lines[i].equals("") && Character.isLetter(lines[i].charAt(0))) {
                i += 1;
                while (i < lines.length && !lines[i].equals("")) {
                    List<Long> range = Arrays.stream(lines[i].split(" "))
                            .filter(s -> !s.equals(""))
                            .map(Long::parseLong)
                            .toList();
                    this.processed.addRange(range.get(1), range.get(0), range.get(2), count);
                    i += 1;
                }
                count += 1;
            }
        }
    }

    public void part1() {
        List<List<Range>> lists = this.processed.getLists();
        PriorityQueue<Long> minHeap = new PriorityQueue<>();

        for (Long seed : this.processed.getSeeds()) {
            long valueToSearch = seed;
            for (List<Range> list : lists) {
                for (Range range : list) {
                    if (range.start() <= valueToSearch && valueToSearch <= range.start() + range.size()) {
                        valueToSearch = range.end() + Math.abs(valueToSearch - range.start());
                        break;
                    }
                }
            }
            minHeap.add(valueToSearch);
        }
        System.out.println(minHeap.peek());
    }

    public void part2() {
        List<List<Range>> lists = this.processed.getLists();
        Collections.reverse(lists);

        int nThreads = 10;
        ExecutorService executor = Executors.newFixedThreadPool(nThreads);
        List<Future<Long>> futures = new ArrayList<>();

        long max = 100000000;
        long workPerThread = max / nThreads;

        for (int i = 0; i < nThreads; i++) {
            long start = i * workPerThread;
            long end = (i + 1) * workPerThread;

            Future<Long> future = executor.submit(() -> worker(start, end));
            futures.add(future);
        }

        executor.shutdown();

        for (Future<Long> future : futures) {
            try {
                Long result = future.get();
                if (result != null) {
                    System.out.println("Found: " + result);
                    return;
                }
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }

        System.out.println("Not found");
    }

    public Long worker(long start, long end) {
        List<List<Range>> lists = this.processed.getLists();
        for (long i = start; i < end; i++) {
            long valueToSearch = i;
            for (List<Range> list : lists) {
                for (Range range : list) {
                    if (range.end() <= valueToSearch && valueToSearch < range.end() + range.size()) {
                        valueToSearch = range.start() + Math.abs(valueToSearch - range.end());
                        break;
                    }
                }
            }
            if (this.processed.checkSeedRanges(valueToSearch)) {
                return i;
            }
        }
        return null;
    }
}

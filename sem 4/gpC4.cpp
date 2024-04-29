import java.io.*;
import java.util.*;

class ExternalSorting {
    private static final int MEMORY_SIZE = 100; // Number of records that can be sorted in memory at a time

    // Function to perform external sorting
    public static void externalSort(String inputFileName, String outputFileName) throws IOException {
        List<String> tempFiles = new ArrayList<>();

        // Step 1: Splitting Phase (External Merge Sort)
        try (BufferedReader br = new BufferedReader(new FileReader(inputFileName))) {
            List<Integer> block = new ArrayList<>();
            String line;
            int tempFileNum = 0;

            while ((line = br.readLine()) != null) {
                block.add(Integer.parseInt(line));

                // If block size reaches memory limit, sort and write to temporary file
                if (block.size() >= MEMORY_SIZE) {
                    Collections.sort(block); // Internal sorting

                    // Write sorted block to a temporary file
                    String tempFileName = "temp" + tempFileNum + ".txt";
                    try (BufferedWriter bw = new BufferedWriter(new FileWriter(tempFileName))) {
                        for (int num : block) {
                            bw.write(Integer.toString(num));
                            bw.newLine();
                        }
                    }
                    tempFiles.add(tempFileName);
                    block.clear();
                    tempFileNum++;
                }
            }

            // Handle the last block if it's not empty
            if (!block.isEmpty()) {
                Collections.sort(block); // Internal sorting
                String tempFileName = "temp" + tempFileNum + ".txt";
                try (BufferedWriter bw = new BufferedWriter(new FileWriter(tempFileName))) {
                    for (int num : block) {
                        bw.write(Integer.toString(num));
                        bw.newLine();
                    }
                }
                tempFiles.add(tempFileName);
            }
        }

        // Step 2: Merging Phase (Multiway Merge)
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(outputFileName))) {
            List<BufferedReader> readers = new ArrayList<>();
            PriorityQueue<Integer> minHeap = new PriorityQueue<>();
            Map<BufferedReader, Integer> bufferedReaderToValue = new HashMap<>();

            // Open readers for each temporary file
            for (String fileName : tempFiles) {
                BufferedReader reader = new BufferedReader(new FileReader(fileName));
                readers.add(reader);
                int value = Integer.parseInt(reader.readLine());
                minHeap.offer(value);
                bufferedReaderToValue.put(reader, value);
            }

            // Multiway merge using min-heap
            while (!minHeap.isEmpty()) {
                int minValue = minHeap.poll();
                bw.write(Integer.toString(minValue));
                bw.newLine();

                for (BufferedReader reader : readers) {
                    int nextValue = bufferedReaderToValue.get(reader);
                    if (nextValue == minValue) {
                        String line = reader.readLine();
                        if (line != null) {
                            int newValue = Integer.parseInt(line);
                            bufferedReaderToValue.put(reader, newValue);
                            minHeap.offer(newValue);
                        } else {
                            reader.close();
                        }
                        break;
                    }
                }
            }

            // Close all readers and delete temporary files
            for (BufferedReader reader : readers) {
                reader.close();
            }
            for (String fileName : tempFiles) {
                new File(fileName).delete();
            }
        }
    }

    // Main method to demonstrate external sorting
    public static void main(String[] args) {
        String inputFileName = "input.txt";
        String outputFileName = "output.txt";

        try {
            externalSort(inputFileName, outputFileName);
            System.out.println("External sorting completed successfully.");
        } catch (IOException e) {
            System.err.println("Error during external sorting: " + e.getMessage());
        }
    }
}

import java.util.Scanner;

public class Priority {
    public static void main(String args[]) {
        Scanner s = new Scanner(System.in);
        int x, n, p[], pp[], bt[], w[], t[], awt = 0, atat = 0, i;
        p = new int[10];
        pp = new int[10];
        bt = new int[10];
        w = new int[10];
        t = new int[10];

        // n is number of processes
        // p is process
        // pp is process priority
        // bt is process burst time
        // w is wait time
        // t is turnaround time
        // awt is average waiting time
        // atat is average turnaround time

        System.out.print("Enter the number of processes: ");
        n = s.nextInt();
        System.out.print("\n\tEnter burst time and priorities:\n");

        for (i = 0; i < n; i++) {
            System.out.print("\nProcess[" + (i + 1) + "]: ");
            bt[i] = s.nextInt(); // Burst Time
            pp[i] = s.nextInt(); // Priority
            p[i] = i + 1; // Process Number
        }

        // Sorting on the basis of priority
        for (i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (pp[i] < pp[j]) { // Higher number means higher priority
                    // Swap priorities
                    x = pp[i];
                    pp[i] = pp[j];
                    pp[j] = x;

                    // Swap burst times
                    x = bt[i];
                    bt[i] = bt[j];
                    bt[j] = x;

                    // Swap process numbers
                    x = p[i];
                    p[i] = p[j];
                    p[j] = x;
                }
            }
        }

        // First process has 0 waiting time
        w[0] = 0;
        t[0] = bt[0];
        atat = t[0];

        for (i = 1; i < n; i++) {
            w[i] = t[i - 1];
            awt += w[i];

            t[i] = w[i] + bt[i];
            atat += t[i];
        }

        // Displaying the process
        System.out.print("\n\nProcess \t Burst Time \t Wait Time \t Turnaround Time \t Priority\n");
        for (i = 0; i < n; i++) {
            System.out.print("\n " + p[i] + "\t\t " + bt[i] + "\t\t " + w[i] + "\t\t " + t[i] + "\t\t " + pp[i] + "\n");
        }

        awt /= n;
        atat /= n;
        System.out.print("\nAverage Wait Time: " + awt);
        System.out.print("\nAverage Turnaround Time: " + atat);

        s.close(); // Close the scanner
    }
}

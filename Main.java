import java.util.*;
enum SchedulingAlgorithm {
    FCFS, SJF, PRIORITY, ROUND_ROBIN
}
class Process {
    int pid, arrivalTime, burstTime, remainingTime, priority;
    int waitingTime, turnaroundTime, completionTime;
    Process(int pid, int at, int bt, int pr) {
        this.pid = pid;
        this.arrivalTime = at;
        this.burstTime = bt;
        this.remainingTime = bt;
        this.priority = pr;
    }
}
class Scheduler {
    List<Process> processes = new ArrayList<>();
    int timeQuantum;
    Scheduler(int tq) {
        this.timeQuantum = tq;
    }
    void addProcess(int id, int at, int bt, int pr) {
        processes.add(new Process(id, at, bt, pr));
    }
    void resetProcesses() {
        for (Process p : processes) {
            p.remainingTime = p.burstTime;
            p.waitingTime = p.turnaroundTime = p.completionTime = 0;
        }
    }
    void FCFS() {
        resetProcesses();
        int time = 0;
        processes.sort(Comparator.comparingInt(p -> p.arrivalTime));
        for (Process p : processes) {
            if (time < p.arrivalTime) time = p.arrivalTime;
            p.waitingTime = time - p.arrivalTime;
            time += p.burstTime;
            p.completionTime = time;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
        }
        display("FCFS");
    }
    void SJF() {
        resetProcesses();
        int time = 0, completed = 0;
        List<Process> ready = new ArrayList<>();
        while (completed < processes.size()) {
            for (Process p : processes) {
                if (p.arrivalTime <= time && p.remainingTime > 0 && !ready.contains(p)) {
                    ready.add(p);
                }
            }
            if (ready.isEmpty()) {
                time++;
                continue;
            }
            ready.sort((a, b) -> a.burstTime != b.burstTime ? a.burstTime - b.burstTime : a.arrivalTime - b.arrivalTime);
            Process p = ready.remove(0);
            p.waitingTime = time - p.arrivalTime;
            time += p.burstTime;
            p.completionTime = time;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.remainingTime = 0;
            completed++;
        }
        display("SJF");
    }
    void Priority() {
        resetProcesses();
        int time = 0, completed = 0;
        List<Process> ready = new ArrayList<>();
        while (completed < processes.size()) {
            for (Process p : processes) {
                if (p.arrivalTime <= time && p.remainingTime > 0 && !ready.contains(p)) {
                    ready.add(p);
                }
            }
            if (ready.isEmpty()) {
                time++;
                continue;
            }
            ready.sort((a, b) -> a.priority != b.priority ? a.priority - b.priority : a.arrivalTime - b.arrivalTime);
            Process p = ready.remove(0);
            p.waitingTime = time - p.arrivalTime;
            time += p.burstTime;
            p.completionTime = time;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.remainingTime = 0;
            completed++;
        }
        display("Priority");
    }
    void RoundRobin() {
        resetProcesses();
        int time = 0;
        Queue<Process> queue = new LinkedList<>();
        boolean[] inQueue = new boolean[processes.size()];

        for (int i = 0; i < processes.size(); i++) {
            if (processes.get(i).arrivalTime <= time) {
                queue.add(processes.get(i));
                inQueue[i] = true;
            }
        }
        while (!queue.isEmpty()) {
            Process current = queue.poll();
            int execTime = Math.min(timeQuantum, current.remainingTime);
            time = Math.max(time, current.arrivalTime) + execTime;
            current.remainingTime -= execTime;

            for (int i = 0; i < processes.size(); i++) {
                Process p = processes.get(i);
                if (p.arrivalTime <= time && p.remainingTime > 0 && !inQueue[i]) {
                    queue.add(p);
                    inQueue[i] = true;
                }
            }

            if (current.remainingTime > 0) {
                queue.add(current);
            } else {
                current.completionTime = time;
                current.turnaroundTime = current.completionTime - current.arrivalTime;
                current.waitingTime = current.turnaroundTime - current.burstTime;
            }
        }
        display("Round Robin");
    }
    void display(String method) {
        double totalWT = 0, totalTAT = 0;
        System.out.println("\nScheduling: " + method);
        System.out.println("PID\tAT\tBT\tPR\tCT\tTAT\tWT");
        for (Process p : processes) {
            System.out.printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p.pid, p.arrivalTime, p.burstTime, p.priority,
                    p.completionTime, p.turnaroundTime, p.waitingTime);
            totalWT += p.waitingTime;
            totalTAT += p.turnaroundTime;
        }
        System.out.printf("Average WT: %.2f\n", totalWT / processes.size());
        System.out.printf("Average TAT: %.2f\n", totalTAT / processes.size());
    }
}
public class Main {
    public static void main(String[] args) {
        Scheduler scheduler = new Scheduler(3);
        scheduler.addProcess(1, 0, 8, 3);
        scheduler.addProcess(2, 1, 4, 1);
        scheduler.addProcess(3, 2, 9, 4);
        scheduler.addProcess(4, 3, 5, 2);
        scheduler.addProcess(5, 4, 2, 5);
        scheduler.FCFS();
        scheduler.SJF();
        scheduler.Priority();
        scheduler.RoundRobin();
    }
}

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <string>
#include <memory>
using namespace std;
enum class SchedulingAlgorithm
{
    FCFS,
    SJF,
    PRIORITY,
    ROUND_ROBIN
};
class Process
{
public:
    int pid, arrival_time, burst_time, remaining_time, priority;
    int waiting_time, turnaround_time, completion_time;

    Process(int id, int at, int bt, int pr = 0)
        : pid(id), arrival_time(at), burst_time(bt), remaining_time(bt),
          priority(pr), waiting_time(0), turnaround_time(0), completion_time(0) {}
};

bool compareArrival(const shared_ptr<Process>& a, const shared_ptr<Process>& b)
{
    return a->arrival_time < b->arrival_time;
}

bool compareBurst(const shared_ptr<Process>& a, const shared_ptr<Process>& b)
{
    if(a->burst_time == b->burst_time)
        return a->arrival_time < b->arrival_time;
    return a->burst_time < b->burst_time;
}

bool comparePriority(const shared_ptr<Process>& a, const shared_ptr<Process>& b)
{
    if(a->priority == b->priority)
        return a->arrival_time < b->arrival_time;
    return a->priority < b->priority;
}
class Scheduler
{
    vector<shared_ptr<Process>> processes;
    int time_quantum;

public:
    Scheduler(int tq = 2) : time_quantum(tq) {}
    void addProcess(int id, int at, int bt, int pr = 0)
    {
        processes.push_back(make_shared<Process>(id, at, bt, pr));
    }

    void resetProcesses()
    {
        for(auto& p : processes)
        {
            p->remaining_time = p->burst_time;
            p->waiting_time = p->turnaround_time = p->completion_time = 0;
        }
    }

    void FCFS()
    {
        resetProcesses();
        int time = 0;
        sort(processes.begin(), processes.end(), compareArrival);
        for(auto& p : processes)
        {
            if(time < p->arrival_time) time = p->arrival_time;
            p->waiting_time = time - p->arrival_time;
            time += p->burst_time;
            p->completion_time = time;
            p->turnaround_time = p->completion_time - p->arrival_time;
        }
        display("FCFS");
    }

    void SJF()
    {
        resetProcesses();
        int time = 0, completed = 0;
        vector<shared_ptr<Process>> ready;
        while(completed < processes.size())
        {
            for(auto& p : processes)
            {
                if(p->arrival_time <= time && p->remaining_time > 0)
                    ready.push_back(p);
            }
            if(ready.empty())
            {
                time++;
                continue;
            }
            sort(ready.begin(), ready.end(), compareBurst);
            auto p = ready.front();
            ready.clear();
            p->waiting_time = time - p->arrival_time;
            time += p->burst_time;
            p->completion_time = time;
            p->turnaround_time = p->completion_time - p->arrival_time;
            p->remaining_time = 0;
            completed++;
        }
        display("SJF");
    }

    void Priority()
    {
        resetProcesses();
        int time = 0, completed = 0;
        vector<shared_ptr<Process>> ready;
        while(completed < processes.size())
        {
            for(auto& p : processes)
            {
                if(p->arrival_time <= time && p->remaining_time > 0)
                    ready.push_back(p);
            }
            if(ready.empty())
            {
                time++;
                continue;
            }
            sort(ready.begin(), ready.end(), comparePriority);
            auto p = ready.front();
            ready.clear();
            p->waiting_time = time - p->arrival_time;
            time += p->burst_time;
            p->completion_time = time;
            p->turnaround_time = p->completion_time - p->arrival_time;
            p->remaining_time = 0;
            completed++;
        }
        display("Priority");
    }

    void RoundRobin()
    {
        resetProcesses();
        int time = 0, completed = 0;
        queue<shared_ptr<Process>> q;
        vector<bool> in_queue(processes.size(), false);
        auto push_ready = [&](int t)
        {
            for(int i=0; i<processes.size(); i++)
            {
                if(processes[i]->arrival_time <= t && processes[i]->remaining_time > 0 && !in_queue[i])
                {
                    q.push(processes[i]);
                    in_queue[i] = true;
                }
            }
        };

        push_ready(0);
        while(!q.empty())
        {
            auto p = q.front();
            q.pop();
            int exec = std::min(time_quantum, p->remaining_time);
            time = std::max(time, p->arrival_time) + exec;
            p->remaining_time -= exec;
            push_ready(time);
            if(p->remaining_time > 0) q.push(p);
            else
            {
                p->completion_time = time;
                p->turnaround_time = p->completion_time - p->arrival_time;
                p->waiting_time = p->turnaround_time - p->burst_time;
                completed++;
            }
        }
        display("Round Robin");
    }

    void display(const string& method)
    {
        double total_wt = 0, total_tat = 0;
        cout << "\nScheduling: " << method << "\n";
        cout << "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n";
        for(auto& p : processes)
        {
            cout << p->pid << "\t" << p->arrival_time << "\t" << p->burst_time << "\t"
                 << p->priority << "\t" << p->completion_time << "\t"
                 << p->turnaround_time << "\t" << p->waiting_time << "\n";
            total_wt += p->waiting_time;
            total_tat += p->turnaround_time;
        }
        cout << "Average WT: " << total_wt / processes.size() << "\n";
        cout << "Average TAT: " << total_tat / processes.size() << "\n";
    }
};
int main()
{
    Scheduler s(3);
    s.addProcess(1, 0, 8, 3);
    s.addProcess(2, 1, 4, 1);
    s.addProcess(3, 2, 9, 4);
    s.addProcess(4, 3, 5, 2);
    s.addProcess(5, 4, 2, 5);
    s.FCFS();
    s.SJF();
    s.Priority();
    s.RoundRobin();
    return 0;
}

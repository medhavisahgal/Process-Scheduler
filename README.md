# 🖥️ OS Process Scheduler Simulator in C++

## 📌 Description

This project simulates various **CPU Scheduling Algorithms** used in Operating Systems, implemented in **C++**. It covers:

- **First Come First Serve (FCFS)**
- **Shortest Job First (SJF)**
- **Priority Scheduling**
- **Round Robin (RR)**

Each algorithm calculates essential process performance metrics such as **Waiting Time, Turnaround Time, Completion Time**, and displays a summary table after execution.

---

## 🚀 Features

- Supports 4 fundamental CPU Scheduling algorithms.
- Computes:
  - Completion Time
  - Turnaround Time
  - Waiting Time
  - Average Waiting & Turnaround Time
- Clean tabular output for process details.
- Easily extendable (code structured using **`struct`** and **`enum`**).

---

## 🛠️ Technologies Used

- **Language:** C++
- **Concepts:** Struct, Enum, Vectors, Queues, Sorting, Scheduling Algorithms
---
### Scheduling: FCFS

| PID | AT | BT | PR | CT | TAT | WT |
|-----|----|----|----|----|-----|----|
|  1  | 0  | 8  | 3  | 8  |  8  | 0  |
|  2  | 1  | 4  | 1  | 12 | 11  | 7  |
|  3  | 2  | 9  | 4  | 21 | 19  | 10 |
|  4  | 3  | 5  | 2  | 26 | 23  | 18 |
|  5  | 4  | 2  | 5  | 28 | 24  | 22 |

**Average WT:** 11.40  
**Average TAT:** 17.00

---

## 💻 How to Run

### 1. **Clone the repository:**
```bash
git clone https://github.com/medhavisahgal/Process-Scheduler.git
cd Process-Scheduler
```
### 2. **Compile the program:**
```
g++ process_scheduler.cpp -o scheduler
./scheduler
```
### 3. **Run the executable:**
```
📂 File Structure
bash
Copy code
├── process_scheduler.cpp   # Main C++ source file
├── README.md      # Project documentation
```
## ✨ Future Improvements
- Add support for Multi-Level Feedback Queue (MLFQ).

- Implement Preemptive SJF and Priority Scheduling.

- GUI or web-based Gantt chart visualization.

## 🤝 Contributions
Contributions, issues, and feature requests are welcome!
Feel free to check issues.

## 📃 License
This project is licensed under the **MIT License**.



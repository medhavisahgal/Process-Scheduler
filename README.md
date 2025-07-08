# 🖥️ OS Process Scheduler Simulator in Java
## 📌 Description
This project simulates key **CPU Scheduling Algorithms** used in Operating Systems, implemented in **Java**. It covers:

- ✅ First Come First Serve (FCFS)
- ✅ Shortest Job First (SJF)
- ✅ Priority Scheduling
- ✅ Round Robin (RR)

Each algorithm computes essential process performance metrics such as:

- Completion Time (CT)
- Turnaround Time (TAT)
- Waiting Time (WT)

And outputs a summary table after execution.

---

## 🚀 Features

- Simulates 4 fundamental CPU Scheduling algorithms
- Calculates:
  - ⏱️ Completion Time
  - 🔁 Turnaround Time
  - ⌛ Waiting Time
  - 📊 Average WT & TAT
- Clean tabular console output
- Modular, extensible design using Java classes and enums

---

## 🛠️ Technologies Used

- **Language:** Java
- **Concepts:** OOP, Enums, Lists, Queues, Sorting, Scheduling Algorithms

---

## 🧪 Sample Output: FCFS

| PID | AT | BT | PR | CT | TAT | WT |
|-----|----|----|----|----|-----|----|
|  1  | 0  | 8  | 3  | 8  |  8  | 0  |
|  2  | 1  | 4  | 1  | 12 | 11  | 7  |
|  3  | 2  | 9  | 4  | 21 | 19  | 10 |
|  4  | 3  | 5  | 2  | 26 | 23  | 18 |
|  5  | 4  | 2  | 5  | 28 | 24  | 22 |

**Average WT:** `11.40`  
**Average TAT:** `17.00`

---

## 💻 How to Run

### 1. **Clone the repository**
```bash
git clone https://github.com/medhavisahgal/Process-Scheduler.git
cd Process-Scheduler
````

### 2. **Compile the Java file**

```bash
javac Main.java
```

### 3. **Run the simulator**

```bash
java Main
```

---

## 📁 File Structure

```
📦 Process-Scheduler
├── Main.java         # Main Java class (entry point)
├── README.md         # Project documentation
```

---

## ✨ Future Improvements

* ✅ Add Preemptive SJF and Preemptive Priority
* 🔁 Add support for Multi-Level Feedback Queue (MLFQ)
* 🎨 GUI or web-based Gantt Chart visualization (JavaFX or Web)

---

## 🤝 Contributions

Contributions, issues, and feature requests are welcome!
Feel free to fork the repo, open issues, or submit PRs. 💬

---

## 📃 License

This project is licensed under the **MIT License** – see the [LICENSE](LICENSE) file for details.




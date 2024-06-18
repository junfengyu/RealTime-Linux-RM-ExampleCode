
# Real-Time Scheduler Analysis

This project provides an example of using the Rate Monotonic (RM) scheduling algorithm in a real-time Linux environment. The code includes CPU affinity settings for assigning each task to a specific CPU core and performs a schedulability analysis to ensure that the given tasks can meet their deadlines.

## Features

- **Rate Monotonic Scheduling**: Assigns static priorities to tasks based on their periodicity.
- **CPU Affinity**: Ensures tasks run on designated CPU cores.
- **Schedulability Analysis**: Checks if tasks meet their deadlines using utilization and response-time analysis.

## Getting Started

### Prerequisites

- Linux operating system
- GCC compiler
- POSIX thread library

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/realtime-scheduler-analysis.git
   cd realtime-scheduler-analysis
   ```

2. Compile the code:
   ```bash
   gcc -o realtime_scheduler realtime_scheduler.c -lpthread
   ```

### Usage

Run the compiled program:
```bash
./realtime_scheduler
```

The program will output whether the task set is schedulable under Rate Monotonic Scheduling and display the response times for each task.

## Python Script for Schedulability Analysis

A Python script is provided to perform the schedulability analysis. This script calculates the total CPU utilization and performs response-time analysis for the tasks.

### Running the Python Script

1. Ensure you have Python installed on your system.
2. Run the script:
   ```bash
   python3 scheduler_analysis.py
   ```

### Sample Output

```
Total Utilization: 0.3000
Within Utilization Bound: Yes
The task set is schedulable with the following response times:
Task 1: Response Time = 100 ms, Deadline = 1000 ms
Task 2: Response Time = 150 ms, Deadline = 500 ms
Task 3: Response Time = 175 ms, Deadline = 250 ms
```

### Step-by-Step Analysis:

#### 1. Calculate Utilization
For RM scheduling, the utilization \( U \) must satisfy the inequality:
\[ U \leq n \times (2^{1/n} - 1) \]
where \( n \) is the number of tasks.

#### 2. Response-Time Analysis
For each task, we need to check if it meets its deadline. The response time \( R_i \) of task \( \tau_i \) can be calculated iteratively:
\[ R_i^{(k+1)} = C_i + \sum_{j < i} \left\lceil \frac{R_i^{(k)}}{T_j} \right\rceil C_j \]
where \( C_i \) is the computation time and \( T_i \) is the period of task \( \tau_i \).

# Perform the analysis
utilization_result, within_bound = check_utilization_bound(tasks)
schedulable, response_times = response_time_analysis(tasks)

# Output the results
print(f"Total Utilization: {utilization_result:.4f}")
print(f"Within Utilization Bound: {'Yes' if within_bound else 'No'}")

if schedulable:
    print("The task set is schedulable with the following response times:")
    for i, R in enumerate(response_times):
        print(f"Task {i+1}: Response Time = {R} ms, Deadline = {tasks[i]['period']} ms")
else:
    print("The task set is not schedulable under Rate Monotonic Scheduling.")
```

### Explanation
- **Utilization Calculation**: Compute the total CPU utilization by summing up the ratio of computation time to period for each task.
- **Utilization Bound Check**: Compare the total utilization against the RM schedulability bound.
- **Response-Time Analysis**: Calculate the response time for each task iteratively and check if it is within the task's period (deadline).

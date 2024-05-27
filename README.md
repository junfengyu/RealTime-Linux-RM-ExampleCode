```markdown
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

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.


**Suggestions for next steps:**
**a.** Add unit tests to validate the task execution and timing.
**b.** Implement logging to track the execution and scheduling behavior of tasks in real-time.

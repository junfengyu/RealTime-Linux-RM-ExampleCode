import math

# Define the tasks with their periods and computation times
tasks = [
    {"period": 1000, "computation_time": 100},  # Task 1
    {"period": 500, "computation_time": 50},    # Task 2
    {"period": 250, "computation_time": 25}     # Task 3
]

# Calculate total utilization
def utilization(tasks):
    return sum(task["computation_time"] / task["period"] for task in tasks)

# Check utilization bound
def check_utilization_bound(tasks):
    n = len(tasks)
    U = utilization(tasks)
    bound = n * (2 ** (1 / n) - 1)
    return U, U <= bound

# Response-time analysis for each task
def response_time_analysis(tasks):
    n = len(tasks)
    response_times = [0] * n

    for i in range(n):
        task = tasks[i]
        R = task["computation_time"]
        while True:
            R_new = task["computation_time"]
            for j in range(i):
                R_new += math.ceil(R / tasks[j]["period"]) * tasks[j]["computation_time"]
            if R_new == R:
                break
            if R_new > task["period"]:
                return False, None
            R = R_new
        response_times[i] = R

    return True, response_times

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

# Milestone 03 - Timing and Memory Fundamentals

## 1. Objective

The objective of this milestone is to understand how the execution time of a C application changes when the number of samples increases.

We developed a C-based application that generates two sinusoidal signals with frequencies of 50 Hz and 120 Hz and combines them into a composite signal.

We measured the execution time for three different sample counts: 1,000, 10,000 and 100,000.

Each experiment was repeated 10 times to observe how execution time varies between runs.

The results were stored in a CSV file and visualized using Python, Pandas and Matplotlib.

Memory consumption and dynamic memory allocation will be investigated separately.

## 2. Concepts Learned

### 2.1 POSIX API

POSIX stands for Portable Operating System Interface.

It is a set of standards that defines interfaces for operating systems, including functions used for file handling, processes, threads and timing.

In this milestone, we used the POSIX function `clock_gettime()` to measure execution time.

### 2.2 clock_gettime()

The `clock_gettime()` function is used to record a timestamp from a specified clock.

We used `CLOCK_MONOTONIC` because it is suitable for measuring elapsed time and is not affected by ordinary system clock adjustments.

The process is:

1. Record the timestamp before generating the samples.
2. Generate the sinusoidal signals.
3. Record the timestamp after generating the samples.
4. Calculate the difference between the timestamps.

Elapsed time = End time - Start time

To calculate elapsed time in milliseconds:

```c
double timeElapsedMs =
    (EndTime.tv_sec - StartTime.tv_sec) * 1000.0 +
    (EndTime.tv_nsec - StartTime.tv_nsec) / 1000000.0;
```

### 2.3 struct timespec

The `struct timespec` structure is defined in the `<time.h>` header.

It represents time using seconds and nanoseconds.

```c
struct timespec
{
    time_t tv_sec;    // Seconds
    long tv_nsec;     // Nanoseconds
};
```

- `tv_sec` stores the number of whole seconds.
- `tv_nsec` stores the nanosecond portion of the timestamp.

Time conversion:

- 1 second = 1,000 milliseconds
- 1 millisecond = 1,000 microseconds
- 1 microsecond = 1,000 nanoseconds
- 1 millisecond = 1,000,000 nanoseconds

### 2.4 File Handling

We used file-handling functions to store benchmarking results in a CSV file.

**fopen()**

Used to open a file.

We used append mode (`"a"`) so that new measurements could be added without overwriting previous results.

**fseek()**

Used to move the file position indicator to a specified location.

We used it to move to the end of the CSV file.

**ftell()**

Used to determine the current file position.

We used it to check whether the CSV file was empty before writing the header.

**fprintf()**

Used to write formatted benchmarking results to the CSV file.

**fclose()**

Used to close the file after writing the results.

### 2.5 Average and Median Execution Time

When we execute the same application multiple times, the execution time may vary.

This can happen because of operating-system scheduling, CPU frequency changes, caching and other system activities.

Consider five execution-time measurements:

3 ms, 3 ms, 4 ms, 5 ms, 20 ms

Average = (3 + 3 + 4 + 5 + 20) / 5 = 7 ms

Median = 4 ms

In this example, four executions finished between 3 and 5 ms, but one execution took 20 ms.

The slower execution could have occurred because Linux temporarily interrupted the program to perform another task.

The average includes all measurements and is affected by the unusually slow execution.

The median represents the middle value and is less affected by unusually slow measurements.

For our benchmarking experiment, we used the median to estimate the typical execution time for each sample count.

However, the average and maximum execution times are also important when analyzing overall performance.

## 3. Implementation

The application was developed in C and executed in Ubuntu using WSL2.

The program performs the following operations:

1. Generate two sine waves with frequencies of 50 Hz and 120 Hz.
2. Combine the sine waves into a composite signal.
3. Measure execution time using `clock_gettime()`.
4. Repeat the signal-generation process 10 times.
5. Store the sample count, iteration number and execution time in a CSV file.
6. Repeat the experiment for 1,000, 10,000 and 100,000 samples.
7. Use Python to analyze and visualize the benchmarking results.

### Python Visualization

We used Pandas to read the CSV file and Matplotlib to generate two graphs.

The `groupby()` function was used to group measurements having the same sample count.

The `median()` function was then used to calculate one representative execution time for each sample count.

Two plots were created:

1. Median execution time versus sample count.
2. Scatter plot showing all individual execution-time measurements.

## 4. Results

### 4.1 Execution Time for 1,000 Samples

| Iteration | Execution Time (ms) |
|---|---|
| 0 | 0.044322 |
| 1 | 0.035063 |
| 2 | 0.035721 |
| 3 | 0.032991 |
| 4 | 0.032594 |
| 5 | 0.032905 |
| 6 | 0.035575 |
| 7 | 0.034272 |
| 8 | 0.031431 |
| 9 | 0.031448 |

### 4.2 Execution Time for 10,000 Samples

| Iteration | Execution Time (ms) |
|---|---|
| 0 | 0.815317 |
| 1 | 0.325189 |
| 2 | 0.321337 |
| 3 | 0.342960 |
| 4 | 0.319310 |
| 5 | 0.301016 |
| 6 | 0.240765 |
| 7 | 0.253842 |
| 8 | 0.238483 |
| 9 | 0.324998 |

### 4.3 Execution Time for 100,000 Samples

| Iteration | Execution Time (ms) |
|---|---|
| 0 | 2.945364 |
| 1 | 3.390342 |
| 2 | 7.150102 |
| 3 | 2.488418 |
| 4 | 2.393206 |
| 5 | 3.397157 |
| 6 | 4.442859 |
| 7 | 5.496260 |
| 8 | 3.530546 |
| 9 | 2.990080 |

### 4.4 Median Execution-Time Comparison

| Sample Count | Median Execution Time (ms) |
|---|---|
| 1,000 | 0.033632 |
| 10,000 | 0.320324 |
| 100,000 | 3.393750 |

## 5. Observations

### 5.1 Median Execution-Time Plot

The median execution time increases as the number of samples increases.

This suggests that the signal-generation algorithm has approximately linear execution-time growth for the sample counts tested.

However, this does not mean that the CPU takes exactly the same amount of time for every sample or every execution.

The graph only shows how the typical measured execution time changes with workload size.

### 5.2 Scatter Plot

The scatter plot shows the execution times of all 10 iterations for each sample count.

Observations:

- **1,000 samples:** Execution times are very small and close together.
- **10,000 samples:** Execution times are higher, with some variation between iterations.
- **100,000 samples:** Execution times vary more significantly, with one measurement exceeding 7 ms in the recorded results.

These observations show that increasing the workload generally increases execution time.

They also demonstrate that executing the same program multiple times does not always produce identical timing results.

Possible reasons include Linux scheduling, CPU frequency changes, cache behavior and system activity.

## 6. Conclusion

In this milestone, we developed a C-based benchmarking application to measure the execution time of sinusoidal signal generation.

We used the Linux POSIX `clock_gettime()` API to record timestamps and calculate processing time.

The application was tested using 1,000, 10,000 and 100,000 samples, with 10 repetitions for each workload.

Benchmarking results were saved in a CSV file and analyzed using Python, Pandas and Matplotlib.

We learned how to use median execution time to represent typical performance and scatter plots to observe variation between individual runs.

The results suggest that execution time increases approximately linearly with sample count for the workloads tested.

This provides a foundation for future performance benchmarking, memory analysis and optimization of DSP applications.
# Milestone 01 — Linux and Embedded Fundamentals

## 1. Objective

The objective of this milestone is to become familiar with the Linux development environment and develop a basic C application that generates 100 numerical samples and stores them in a text file.

## 2. Problem Statement

Consider a temperature sensor that generates 100 numerical measurements.

Since no physical hardware is being used during the initial learning phase, a C program will simulate the temperature measurements.

The generated samples will be stored in a text file for future processing and analysis.

The sample-generation formula is:

**x[n] = 25.0 + 0.5n**

Where:

- `x[n]` represents the generated sample value.
- `n` represents the sample index, starting from zero.
- `25.0` represents the initial temperature value.
- `0.5` represents the increment between consecutive samples.

For example:

- n = 0 → x[0] = 25.0 + 0.5(0) = 25.0
- n = 1 → x[1] = 25.0 + 0.5(1) = 25.5
- n = 2 → x[2] = 25.0 + 0.5(2) = 26.0
- n = 99 → x[99] = 25.0 + 0.5(99) = 74.5

Therefore, the program generates 100 samples, increasing by 0.5 with each sample.

## 3. Development Environment

The development environment consists of:

**WSL2 — Windows Subsystem for Linux**

Allows a Linux kernel and Linux user-space environment to run on Windows.

**Ubuntu**

A Linux distribution providing system utilities, libraries and package-management tools.

**GCC**

GNU Compiler Collection, used to compile the C application.

**GDB**

GNU Debugger, used to debug the compiled application and inspect variables.

**GNU Make**

A build automation tool for managing compilation commands and dependencies.

**Visual Studio Code**

IDE/editor used for developing, compiling and debugging the application through WSL2.

**Git**

Version-control system used to track source-code changes.

## 4. Basic Linux Commands

| Command | Description |
|---|---|
| `cd ~` | Navigate to the Linux home directory |
| `pwd` | Display the current working directory |
| `whoami` | Display the current Linux username |
| `uname -r` | Display the Linux kernel version |
| `ls -la` | List files and directories, including hidden files |
| `mkdir` | Create a directory |
| `cd` | Change directory |
| `wc -l` | Count the number of lines in a file |
| `head -n 5` | Display the first five lines |
| `tail -n 5` | Display the last five lines |

Example terminal outputs:

```bash
aman@Aman:~$ pwd
/home/aman

aman@Aman:~$ whoami
aman

aman@Aman:~$ uname -r
6.18.58.1-microsoft-standard-WSL2
```

## 5. File Operations in C

The application uses standard C library functions to create a file, write measurements and close the file.

### 5.1 Opening a file

```c
FILE *filePointer = fopen("temperature_samples.txt", "w");
```

The `fopen()` function opens a file stream.

The `"w"` mode opens the file for writing, creates it if necessary and truncates existing contents.

If opening the file fails, `fopen()` returns `NULL`.

### 5.2 Writing to a file

```c
fprintf(filePointer, "%.2f\n", temperatureValue);
```

The `fprintf()` function writes formatted output to the specified file stream.

It returns a negative value if an output error occurs.

### 5.3 Closing a file

```c
fclose(filePointer);
```

The `fclose()` function flushes buffered output and closes the file stream.

It returns zero on success and `EOF` on failure.

### 5.4 Error handling

The application checks whether file opening, writing and closing operations succeed.

```c
perror("Error opening file");
```

The `perror()` function displays a descriptive error message associated with the current `errno` value.

Unlike `printf()`, it can provide information about the underlying library or operating-system error.

## 6. Implementation

The application follows these steps:

1. Open `temperature_samples.txt` in write mode.
2. Check whether the file was opened successfully.
3. Execute a `for` loop with 100 iterations.
4. Generate each sample using the defined formula.
5. Print the sample value to the console.
6. Write the generated sample to the text file.
7. Check whether writing succeeded.
8. Close the file and check for errors.

## 7. Testing and Validation

The following commands are used to validate the output file.

**Check the number of samples:**

```bash
wc -l temperature_samples.txt
```

Expected result: 100 lines.

**Inspect the first five samples:**

```bash
head -n 5 temperature_samples.txt
```

Expected values:

```text
25.00
25.50
26.00
26.50
27.00
```

**Inspect the last five samples:**

```bash
tail -n 5 temperature_samples.txt
```

Expected values:

```text
72.50
73.00
73.50
74.00
74.50
```

**Verify overwrite behavior:**

Run the application twice and confirm that the file still contains 100 samples.

These are the expected results; record the actual results after testing.

## 8. Key Learnings

This milestone introduces:

- Using Ubuntu through WSL2.
- Basic Linux terminal commands and filesystem navigation.
- Compiling C applications with GCC.
- Debugging C applications using GDB and VS Code.
- Generating numerical samples using a `for` loop.
- Working with file pointers and standard C file I/O.
- Checking return values and handling errors.
- Validating generated data using Linux commands.
- Maintaining project source code and documentation using Git.

## 9. Conclusion

A C application was implemented to simulate 100 numerical measurements and write them to a text file.

This milestone establishes the foundation for subsequent DSP experiments involving signal generation, sampling, filtering and performance analysis.

The next milestone will focus on **digital signal generation and sampling fundamentals**.
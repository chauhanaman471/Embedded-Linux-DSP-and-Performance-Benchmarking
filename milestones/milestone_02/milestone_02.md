# Milestone 02 — Sampling and Signal Generation

## 1. Objective

The objective of this milestone is to understand the fundamentals of digital signal generation and sampling by developing a C application that generates two sinusoidal signals with different frequencies.

The two signals are combined using the principle of superposition, and the resulting samples are stored in a CSV file.

Python is then used to visualize and analyze the generated signals. These samples will also be used in future milestones involving digital signal processing (DSP).

## 2. Problem Statement

Consider an embedded system that needs to generate, process, and analyze signals containing multiple frequency components.

Since physical hardware is not being used during the initial learning phase, the signals are generated mathematically using a C application.

The application must:

1. Generate two sine waves with frequencies of 50 Hz and 120 Hz.
2. Sample both signals at a sampling frequency of 1,000 Hz.
3. Combine the signals through superposition.
4. Store 1,000 samples of each signal in a CSV file.
5. Visualize the individual and composite signals using Python.
6. Verify the generated signals using frequency and period calculations.

## 3. Theory

### 3.1 Sinusoidal Signal Generation

A discrete-time sinusoidal signal can be represented mathematically as:

\[
x[n] = A\sin\left(2\pi f\frac{n}{f_s}\right)
\]

Where:

| Parameter | Description |
|---|---|
| \(x[n]\) | Amplitude of the generated signal at sample index n |
| \(A\) | Amplitude of the sine wave |
| \(f\) | Signal frequency in hertz (Hz) |
| \(f_s\) | Sampling frequency in samples per second (Hz) |
| \(n\) | Sample index |
| \(\pi\) | Mathematical constant pi |

For this milestone, the following parameters are used:

| Parameter | Value |
|---|---|
| Signal 1 frequency | 50 Hz |
| Signal 2 frequency | 120 Hz |
| Signal 1 amplitude | 1.0 |
| Signal 2 amplitude | 1.0 |
| Sampling frequency | 1,000 Hz |
| Number of samples | 1,000 |

### 3.2 Frequency and Time Period

Frequency represents the number of complete oscillations a periodic signal performs in one second.

The time period represents the duration required to complete one oscillation.

The relationship between frequency and period is:

\[
T = \frac{1}{f}
\]

**For Signal 1 (50 Hz):**

\[
T_1 = \frac{1}{50} = 0.02\text{ s} = 20\text{ ms}
\]

Therefore, the 50 Hz sine wave completes one oscillation every 20 milliseconds.

**For Signal 2 (120 Hz):**

\[
T_2 = \frac{1}{120} \approx 0.00833\text{ s} = 8.33\text{ ms}
\]

Therefore, the 120 Hz sine wave completes one oscillation approximately every 8.33 milliseconds.

### 3.3 Sampling Frequency

Sampling is the process of measuring a continuous-time signal at discrete time intervals.

The sampling frequency specifies the number of samples acquired per second.

For this milestone:

\[
f_s = 1000\text{ Hz}
\]

The sampling interval is:

\[
T_s = \frac{1}{f_s}
\]

\[
T_s = \frac{1}{1000} = 0.001\text{ s} = 1\text{ ms}
\]

Therefore, consecutive samples are separated by 1 millisecond.

The total duration represented by 1,000 samples is:

\[
T_{\text{record}} = \frac{N}{f_s} = \frac{1000}{1000} = 1\text{ s}
\]

The sample indices range from 0 to 999, corresponding to time coordinates from 0 to 999 milliseconds.

### 3.4 Signal Superposition

The principle of superposition states that signals can be combined by adding their corresponding amplitudes.

For this milestone, the two generated signals are:

\[
x_1[n] = \sin\left(2\pi 50\frac{n}{1000}\right)
\]

\[
x_2[n] = \sin\left(2\pi 120\frac{n}{1000}\right)
\]

The composite signal is:

\[
x[n] = x_1[n] + x_2[n]
\]

Therefore:

\[
x[n] = \sin\left(2\pi 50\frac{n}{1000}\right) + \sin\left(2\pi 120\frac{n}{1000}\right)
\]

The resulting waveform contains both frequency components.

Depending on the instantaneous amplitudes of the signals, superposition can produce constructive or destructive interference.

### 3.5 Nyquist Sampling Criterion

According to the Nyquist sampling criterion, a band-limited signal must be sampled at a rate greater than twice its highest frequency to avoid aliasing under ideal sampling assumptions.

\[
f_s > 2f_{\max}
\]

The highest generated frequency in this experiment is 120 Hz.

\[
1000 > 2(120)
\]

\[
1000 > 240
\]

Therefore, the selected sampling frequency is sufficient to represent both generated sine waves without aliasing.

## 4. Implementation Using C

The signal-generation application was developed using C and compiled with GCC in the Ubuntu WSL2 environment.

The application follows these steps:

1. Define the frequency, amplitude, sampling frequency, and number of samples.
2. Declare arrays to store the individual sine waves and the composite signal.
3. Open a CSV file using `fopen()`.
4. Generate the two sine waves using the mathematical `sin()` function.
5. Combine the signals by adding their amplitudes at each sample index.
6. Store the generated samples in the arrays.
7. Write the sample index and signal values into the CSV file using `fprintf()`.
8. Check for file operation errors and close the file using `fclose()`.

The C application produces a file named `composite_signal.csv`.

The file contains 1,000 data rows representing one second of generated signal data, along with a header row.

The four columns are:

- Sample Index
- Sine Wave 1
- Sine Wave 2
- Composite Signal

## 5. Python Environment and Visualization

Python is used to visualize and analyze the generated signal samples.

A virtual environment (`.venv`) was created to isolate project-specific dependencies from other Python projects.

The following libraries were installed:

| Library | Purpose |
|---|---|
| NumPy | Numerical arrays and mathematical calculations |
| Pandas | Reading and processing CSV data |
| Matplotlib | Generating and saving time-domain plots |

Pandas is used to read `composite_signal.csv` into a DataFrame.

Since the CSV column names initially contained extra whitespace, the following operation was used:

`data.columns = data.columns.str.strip()`

This removes leading and trailing spaces from column names.

### 5.1 Converting Sample Index to Time

For visualization, each sample index must be associated with its corresponding time coordinate.

\[
t[n] = \frac{n}{f_s}
\]

For a sampling frequency of 1,000 Hz:

\[
t[n] = \frac{n}{1000}
\]

The calculated value is in seconds.

To convert into milliseconds:

\[
t_{\text{ms}}[n] = \frac{n}{f_s}\times1000
\]

The Python implementation uses:

`data["time_ms"] = data["Sample Index"] / samplingRate * 1000`

### 5.2 Selecting the Visualization Window

For easier visualization, only the first 100 milliseconds of the generated signals were plotted.

The time window was selected using Pandas:

`subset = data[data["time_ms"] < 100]`

This selects 100 samples, corresponding to sample indices 0 through 99.

Matplotlib was used to generate and save three separate graphs.

## 6. Results and Observations

### 6.1 Signal 1 — 50 Hz Sine Wave

![50 Hz Sine Wave](../milestones/milestone_02/Sine_wave_50Hz.png)

The first signal has a frequency of 50 Hz and amplitude of 1.0.

Observations:

- The signal completes 5 oscillations in 100 milliseconds.
- The theoretical amplitude ranges from -1 to +1.
- The time period is 20 milliseconds.

Number of cycles:

\[
N_{\text{cycles}} = \frac{100\text{ ms}}{20\text{ ms}} = 5
\]

### 6.2 Signal 2 — 120 Hz Sine Wave

![120 Hz Sine Wave](../milestones/milestone_02/Sine_wave_120Hz.png)

The second signal has a frequency of 120 Hz and amplitude of 1.0.

Observations:

- The signal completes 12 oscillations in 100 milliseconds.
- The theoretical amplitude ranges from -1 to +1.
- The time period is approximately 8.33 milliseconds.

Number of cycles:

\[
N_{\text{cycles}} = \frac{100\text{ ms}}{8.33\text{ ms}} \approx 12
\]

### 6.3 Composite Signal

![Composite Signal](../milestones/milestone_02/Composite_Signal.png)

The composite signal is generated by adding the amplitudes of the two individual sine waves at every sample index.

Observations:

- The resulting waveform is more complex than either individual sine wave.
- The signal contains the 50 Hz and 120 Hz frequency components.
- Constructive interference occurs when the instantaneous signal amplitudes reinforce each other.
- Destructive interference occurs when the instantaneous signal amplitudes oppose each other.
- The theoretical amplitude bounds are -2 to +2, although the waveform does not necessarily reach those limits.

## 7. Testing and Validation

The following checks were performed during development:

| Test | Expected result | Observation |
|---|---|---|
| Signal generation | 1,000 data samples | Generated successfully |
| CSV export | Four columns of signal data | Generated successfully |
| 50 Hz visualization | 5 cycles in 100 ms | Confirmed |
| 120 Hz visualization | 12 cycles in 100 ms | Confirmed |
| Composite visualization | Superposition of both signals | Confirmed |
| Python CSV reading | Data loaded into Pandas | Successful |
| Graph export | Three PNG files | Successful |

The CSV contains 1,000 signal samples and one header row, giving 1,001 lines in total.

## 8. Challenges and Debugging

### 8.1 CSV File Not Found

Initially, Python was unable to locate `composite_signal.csv`.

The problem occurred because Python searched for the file relative to its current working directory.

The issue was resolved by running the Python script from the milestone directory where the CSV file was stored.

**Learning:** Relative file paths depend on the process's current working directory.

### 8.2 Pandas Column Name Error

A `KeyError` occurred while accessing the CSV columns because some column names contained leading whitespace.

The issue was resolved using:

`data.columns = data.columns.str.strip()`

**Learning:** Pandas column names must match exactly, including whitespace and capitalization.

### 8.3 Matplotlib Display Warning

Matplotlib initially produced a warning because the environment used a non-interactive backend.

The issue was resolved by saving the plots as PNG files using `plt.savefig()` instead of displaying them using `plt.show()`.

**Learning:** Matplotlib can generate and save plots without requiring an interactive graphical display.

## 9. Key Learnings

This milestone introduced the following concepts:

- Discrete-time sinusoidal signal generation.
- Relationship between frequency and time period.
- Sampling frequency and sampling interval.
- Sample index to time-coordinate conversion.
- Nyquist sampling criterion.
- Signal superposition.
- Using arrays to store signal samples in C.
- Exporting signal data to CSV files.
- Using Python virtual environments.
- Reading and processing CSV data using Pandas.
- Visualizing signals using Matplotlib.
- Debugging filesystem paths, CSV formatting, and plotting issues.

## 10. Conclusion

In this milestone, a C application was developed to generate two sinusoidal signals with frequencies of 50 Hz and 120 Hz.

The generated signals were combined through superposition and saved as discrete samples in a CSV file.

Python was used to visualize the individual and composite waveforms, and the observed number of cycles matched the theoretical calculations.

This milestone established a foundation for future work involving digital filtering, frequency-domain analysis, Fourier transforms, and DSP performance benchmarking.
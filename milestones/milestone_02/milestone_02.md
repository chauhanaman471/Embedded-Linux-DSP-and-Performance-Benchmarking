Milestone 02 - Sampling and signal generation

In this milestone we will build 2 sinewaves of different frequencies and combine them and save the resulting sample into a file for visualisation which would be done by Python and in future would be used for DSP processing

sinewave formula using samples : x[n] = Asin(2 x 3.14 x f x n x 1 /fs)
where 
n : sample index
A : sinewave amplitude
f : sinewave frequency
fs : sampling frequency

for this milestone we will generate two sinewave of frequency f1 = 50 Hz, f2 = 120 Hz with amplitude 1.0
frequency = how fast does sinewave appears i.e. 1/50 = 0.02 = 20ms i.e. sinewave appears at every 20ms
similarly, the second sinewave appears at every 1/120 = 0.00833 = 8.33 ms i.e. sinewave appears at every 8.33 ms

we will have 1000 samples and sampling frequency 1000 Hz
resulting sinewave 
x[n] = 1.0 sin (2 x 3.14 x 50 x n x 1/1000) + 1.0 sin (2 x 3.14 x 120 x n x 1/1000)

for visualisation purpose we will use python environment, this will ensure dependencies of this project won't interfere with other projects 
we will use following python libraries
1) Numpy : used for array calculations
2) Pandas : used for reading and working with csv data
3) matplotlib : used for creating plots and figures


convert sampled signal into a continuous time variant signal
t[n] = sample_index/sampling frequency 

lets say sampling rate = 1000 Hz so
t[n] = sample_index/1000

Frequency and time relation : T = 1/f

Number of cycles = time duration/T 



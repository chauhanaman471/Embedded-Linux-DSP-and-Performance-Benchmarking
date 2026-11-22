# This file is used to plot the signals from the milestone 02 csv file

# importing the required libraries
# pandas is used to read the csv file
import pandas as pd 
# matplotlib is used to plot the signals
import matplotlib.pyplot as plt

data = pd.read_csv('composite_signal.csv') # reading the csv file

#removing extra spaces from the column 
data.columns = data.columns.str.strip()

#print the first 5 rows of the dataframe
print(data.head())

# sampling rate in Hz
samplingRate = 1000 

# convert sample index to time in milliseconds
data["time_ms"] = data["Sample Index"] / samplingRate * 1000

# print the first 5 rows of the dataframe
print(data.head()) 

#printing first 100 milliseconds
subset = data[data["time_ms"]<100]

#plotting sine wave of frequency 50 Hz
plt.plot(subset["time_ms"],subset["Sine Wave 1"])
plt.ylabel("Amplitude of Sine Wave 1")
plt.xlabel("Time in ms")
plt.title("Sine wave 1")
plt.grid(True)
plt.savefig("Sine_wave_50Hz.png", dpi=300, bbox_inches="tight")
plt.close()

#plotting sine wave of frequency 120 Hz
plt.plot(subset["time_ms"],subset["Sine Wave 2"])
plt.ylabel("Amplitude of Sine Wave 2")
plt.xlabel("Time in ms")
plt.title("Sine wave 2")
plt.grid(True)
plt.savefig("Sine_wave_120Hz.png", dpi=300, bbox_inches="tight")
plt.close()

#plotting composite wave
plt.plot(subset["time_ms"],subset["Composite Signal"])
plt.ylabel("Amplitude of Composite signal")
plt.xlabel("Time in ms")
plt.title("Composite signal")
plt.grid(True)
plt.savefig("Composite_Signal.png", dpi=300, bbox_inches="tight")
plt.close()
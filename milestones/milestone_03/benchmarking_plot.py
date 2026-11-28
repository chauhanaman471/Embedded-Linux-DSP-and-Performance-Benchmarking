#This file is used to read the benchmarking results from milestone 3 file and then based on the results plot the graph
#importing the necessary libraries
import pandas as pd #This library is used to read the benchmarking csv file
import matplotlib.pyplot as plt #This library is used to plot the graph based on the measurement results

data = pd.read_csv('benchmarking.csv') # reading the csv file

#print the first 5 rows and last 5 rows of the dataframe to check if the file is being read properly
#print(data.head())
#print(data.tail())

#plotting the execution time against different sample counts over 10 iterations
#for a given sample count, it generates execution time in 10 different counts 
#all these 10 measurement results are real values but we want to have an estimate idea that for a given sample count, what's the estimated execution count
#We will use median for this case
#Median : when numbers are arranged in smallest to largest, the middle number is median
#why we don't use average instead of median

#group data by sample count first and then select execution_time_ms and find its median
median_execution_time = data.groupby("Sample_Count")["Execution_time_ms"].median()
#print(median_execution_time)

plt.figure(figsize=(8, 5)) #create a blank canvas of size 8 inches wide and 5 inches tall
plt.plot(median_execution_time.index,median_execution_time.values,marker='x')
plt.xscale("log") #since we have samples in 1000,10000,100000, expressing them in log scale makes sense than linear scale
plt.xlabel("Sample Count")
plt.ylabel("Median Execution time in ms")
plt.title("Median Execution time for 1000,10000,100000 sample count over 10 iterations")
plt.grid(True)
plt.savefig("Execution_time.png", dpi=300, bbox_inches="tight")
plt.close()

plt.figure(figsize=(8, 5)) #create a blank canvas of size 8 inches wide and 5 inches tall
plt.scatter(data["Sample_Count"],data["Execution_time_ms"])
plt.xscale("log") #since we have samples in 1000,10000,100000, expressing them in log scale makes sense than linear scale
plt.xlabel("Sample Count")
plt.ylabel("Execution time in ms")
plt.title("Scattered plot for Execution time for 1000,10000,100000 sample count over 10 iterations")
plt.grid(True)
plt.savefig("Execution_time_scattered_plot.png", dpi=300, bbox_inches="tight")
plt.close()

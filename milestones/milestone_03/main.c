//This code will calculate memory requirement and execution time to generate sine wave based on different sample counts
//we will reuse main.c from milestone_02 
//for now we just focussed on generation of sinewave and not on storing and plotting the signal
//This program is used to generate two sine waves with different frequencies and amplitudes
//the generate sine waves are then superimposed to create a composite signal
//we will calculate how long processor will take to generate 1000 samples
//It will also give us an idea when the number of samples increases 1000 to 10000
//how much memory is required to generate the required signals

#include <stdio.h> //include the standard input/output library
#include <math.h> //include the math library for sine function
#include <time.h> //include the time library 

#define NUM_SAMPLES 100000
#define PI 3.14159265358979323846

/*
struct timespec is defined in <time.h> library which is used to represent time with precision of nacosecond
           struct timespec 
           {
               time_t   tv_sec;        // seconds 
               long     tv_nsec;       // nanoseconds
           }
*/

int main()
{
    printf("Generating two sine waves with different frequencies and amplitudes\n");
    const float amplitude1 = 1.0f; //amplitude of the first sine wave
    const float amplitude2 = 1.0f; //amplitude of the second sine wave
    const float frequency1 = 50.0f; //frequency of the first sine wave
    const float frequency2 = 120.0f; //frequency of the second sine wave
    int sample_rate = 1000; //sample rate in Hz
    float sinewave1[NUM_SAMPLES] = {0}; //array to hold the first sine wave 
    float sinewave2[NUM_SAMPLES] = {0}; //array to hold the second sine wave
    float composite_signal[NUM_SAMPLES] = {0}; //array to hold the composite signal
    struct timespec StartTime;
    struct timespec EndTime;
    
    FILE *File_Ptr = fopen("benchmarking.csv", "a"); //open a csv file to store the benchmarking results and append (a) the results instead of overwriting
    if (File_Ptr == 0) //check if the file was opened succesfully
    {
        perror("Error opening file for writing\n");
        return 1; //returning error code
    }
    //we need to write the header of the csv file but the issue is we need to just write it only once when the file is empty
    //else it will print every time the file is run since we are appending the benchmarking results
    //check first if file is empty or not
    if (fseek(File_Ptr, 0, SEEK_END)!=0) //It is used to move the file pointer to the end of the file
    {
        perror("Error in seeking the file pointer to end of file\n");
        return 1; //returning error code 
    }
    long fileSize = ftell(File_Ptr); //It is used to tell the position of file pointer from the beginig of the file
    if (fileSize == -1L)
    {
        perror("Error in getting the size of file\n");
        return 1; //returning the return code
    }

    if (fileSize == 0)
    {
        //this will ensure that the header is written only once
        //write the header of the csv file
        if (fprintf(File_Ptr,"Sample_Count,Iteration,Execution_time_ms\n") < 0) //write the header of the csv
        {
            perror("Error writing to csv header!\n"); //print an error message if writing to the file fails
            fclose(File_Ptr); //close the file before returning error code
            return 1; //returning error code
        }
    }

    
    //we will monitor the measurement time for certain iterations for performance benchmarking
    for (int iterationCount = 0; iterationCount <10; iterationCount++)
    {
    //We will measure time before generating samples
    //check if clock_gettime successfully returns
    if (clock_gettime(CLOCK_MONOTONIC, &StartTime)!=0)
    {
        perror("Failed to read the start time\n");
        return 1;
    }

    for(int idx = 0; idx < NUM_SAMPLES; idx++)
    {
        sinewave1[idx] = amplitude1 * sin(2 * PI * frequency1 * idx / sample_rate); //generate the first sine wave
        sinewave2[idx] = amplitude2 * sin(2 * PI * frequency2 * idx / sample_rate); //generate the second sine wave
        composite_signal[idx] = sinewave1[idx] + sinewave2[idx]; //superimpose the two sine waves to create a composite signal
        /*
        if (fprintf(File_Ptr, "%d, %f, %f, %f\n", idx, sinewave1[idx], sinewave2[idx], composite_signal[idx]) < 0) //write the composite signal to the csv file
        {
            perror("Error writing to csv file!\n"); //print an error message if writing to the file fails
            fclose(File_Ptr); //close the file before returning error code
            return 1; //returning error code
        }
        */
    }

    //We will measure the time after generating all the samples
    //check if clock_gettime successfully returns
    if (clock_gettime(CLOCK_MONOTONIC, &EndTime)!=0)
    {
        perror("Failed to read the end time\n");
        return 1;
    }

    //We will calculate the difference to measure the time required to generate the samples
    //1 second	     ->  1,000 milliseconds
    //1 millisecond	 ->  1,000 microseconds
    //1 microsecond	 ->  1,000 nanoseconds
    //1 millisecond	 ->  1,000,000 nanoseconds
    double timelapsedms = (EndTime.tv_sec - StartTime.tv_sec)*1000 + (EndTime.tv_nsec - StartTime.tv_nsec)/1000000.0;

    printf("Time elapsed for iteration count %d :%.6f ms\n",iterationCount, timelapsedms);

    //We are printing because after generation of samples we are not using the results
    //If compiler optimatization is enabled, GCC may remove some calculations because they won't have any affect on program 
    printf("Final composite sample for iteration count %d: %.6f\n", iterationCount, composite_signal[NUM_SAMPLES - 1]);
    //we are storing the results in the csv file
    if (fprintf(File_Ptr, "%d,%d,%.6f\n", NUM_SAMPLES, iterationCount, timelapsedms) < 0) //write the composite signal to the csv file
        {
            perror("Error writing to csv file!\n"); //print an error message if writing to the file fails
            fclose(File_Ptr); //close the file before returning error code
            return 1; //returning error code
        }

    }

    
    //close the file after writing all the samples and check if closing the file was successful or not
    
    if (fclose(File_Ptr) != 0) //check if the file was closed succesfully
    {
        perror("Error closing file!\n"); //print an error message if closing the file fails
        return 1; //returning error code
    }
    
    return 0;
}
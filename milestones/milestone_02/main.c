//This program is used to generate two sine waves with different frequencies and amplitudes
//the generate sine waves are then superimposed to create a composite signal
//we will then use python to plot the generated signal and analyze its properties
#include <stdio.h> //include the standard input/output library
#include <math.h> //include the math library for sine function
#define NUM_SAMPLES 1000
#define PI 3.14159265358979323846

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

    FILE *File_Ptr = fopen("composite_signal.csv", "w"); //open a csv file to store the composite sine wave
    if (File_Ptr == 0) //check if the file was opened succesfully
    {
        perror("Error opening file for writing\n");
        return 1; //returning error code
    }

    //write the header of the csv file
    if (fprintf(File_Ptr,"Sample Index, Sine Wave 1, Sine Wave 2, Composite Signal\n") < 0) //write the header of the csv
    {
        perror("Error writing to csv header!\n"); //print an error message if writing to the file fails
        fclose(File_Ptr); //close the file before returning error code
        return 1; //returning error code
    }

    for(int idx = 0; idx < NUM_SAMPLES; idx++)
    {
        sinewave1[idx] = amplitude1 * sin(2 * PI * frequency1 * idx / sample_rate); //generate the first sine wave
        sinewave2[idx] = amplitude2 * sin(2 * PI * frequency2 * idx / sample_rate); //generate the second sine wave
        composite_signal[idx] = sinewave1[idx] + sinewave2[idx]; //superimpose the two sine waves to create a composite signal
        if (fprintf(File_Ptr, "%d, %f, %f, %f\n", idx, sinewave1[idx], sinewave2[idx], composite_signal[idx]) < 0) //write the composite signal to the csv file
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
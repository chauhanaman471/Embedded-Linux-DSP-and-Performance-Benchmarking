//The main agenda of this milestone is to get familiar with Linux operations
//Task is to write a simple C program that generates 100 numerical samples and store them in a text file using Linux commands
#include <stdio.h>  //Standard input/output header file

int main(void)
{
    //printf("Hello from Embedded Linux!\n");
    //Open a file in write mode using Linux command and if the file does not exist, create it
    FILE *filePointer = fopen("temperature_samples.txt", "w"); //Opening a file in write mode

    //Check if the file was opened successfully
    if (filePointer == NULL)
    {
        perror("Error opening file!"); //Printing error message if file opening fails
        return 1; //Returning error code
    }
    //Generating 100 numerical samples
    for (int tempSampleCount = 0; tempSampleCount < 100; tempSampleCount++)
    {
        float temperatureValue = 25.0f + 0.5f * tempSampleCount; //Generating sample values starting from 25.0 with an increment of 0.5
        printf("Sample %d: %0.2f\n", tempSampleCount, temperatureValue); //Printing the sample values to the console
        //writing the sample values to the file and check if writing to the file was successful or not
        if (fprintf(filePointer, "%0.2f\n", temperatureValue) < 0)
        {
            perror("Error writing to file!\n"); //Printing error message if writing to the file fails
            fclose(filePointer); //Closing the file before returning error code
            return 1; //Returning error code    
        }
    }
    //closing the file after writing all the samples and check if closing the file was successful or not
    if (fclose(filePointer) != 0)
    {
        perror("Error closing file!\n"); //Printing error message if file closing fails
        return 1; //Returning error code
    }
    return 0;
}
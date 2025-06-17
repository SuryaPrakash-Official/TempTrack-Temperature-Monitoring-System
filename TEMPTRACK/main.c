#include <stdio.h>
#include <stdlib.h>

#define THRESHOLD 95.0

int main()
{
    FILE *file = fopen("C:\\Users\\surya\\OneDrive\\Documents\\C PROJECT\\TEMPERATURE DATA ANALYSIS\\bin\\Debug\\temperature.csv", "r");
    FILE *alertFile = fopen("over threshold.csv", "w");

    if (!file)
    {
        printf("Error: Could not open temperature.csv for reading.\n");
        return 1;
    }
    if (!alertFile)
    {
        printf("Error: Could not open over_threshold.csv for writing.\n");
        fclose(file);
        return 1;
    }

    float temp, sum = 0.0, max, min;
    int count = 0, overCount = 0;

    // READ THE FIRST TEMPERATURE TO INITIALIZE MINIMUM AND MAXIMUM
    if (fscanf(file, "%f", &temp) == 1)
    {
        printf("Temperature 1: %.2f*F\n", temp);

        sum = temp;
        max = min = temp;
        count = 1;
        if (temp > THRESHOLD)
        {
            fprintf(alertFile, "%.2f\n", temp);
            overCount++;
        }

        // READ REMAINING TEMPERATURE
        while (fscanf(file, "%f", &temp) == 1)
        {
            count++;
            printf("Temperature %d: %.2f*F\n", count, temp);

            sum += temp;
            if (temp > max) max = temp;
            if (temp < min) min = temp;
            if (temp > THRESHOLD)
            {
                fprintf(alertFile, "%.2f\n", temp);
                overCount++;
            }
        }

        // DETAILS OF TEMPERATURE DATA
        printf("\n***** DETAILS OF TEMPERATURE DATA *****\n");
        printf("Average Temperature: %.2f*F\n", sum / count);
        printf("Max Temperature: %.2f*F\n", max);
        printf("Min Temperature: %.2f*F\n", min);
        printf("Temperatures over %.1f*F: %d\n", THRESHOLD, overCount);
    }
    else
    {
        printf("No temperature data found in the file.\n");
    }

    fclose(file);
    fclose(alertFile);

    return 0;
}

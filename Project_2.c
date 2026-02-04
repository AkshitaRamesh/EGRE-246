#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Project 2
   Akshita Ramesh and Ziona Tucker
    EGRE 246 - Fall 2023   */

struct seaZone
{

    int vals[1000][5][5][5];
    double average;
};

double allAverages[1000];

int getVals(FILE *initFile);
int getZones(FILE *initFile);
double getAverage(struct seaZone zone, int amZones, double allAverages[]);
double getSmallest(double allAverages[], int amZones);
double getLargest(double allAverages[], int amZones);
double zoneVals(FILE *initFile, struct seaZone zone, int amZones, double allAverages[]);
int getIndex(double allAverages[], double numLookin, int amZones);
void normalizedZone(FILE *normalizedFile, FILE *initFile, double allAverages[], int amZones, struct seaZone zone, int numZone);


int getVals(FILE *initFile)
{

    int n;
    fscanf(initFile, "%d", &n);

    return n;
}

int getZones(FILE *initFile)
{
    // initFile = fopen("seaZone.dat", "r");

    int n;
    fscanf(initFile, "%d", &n);
    // fclose(initFile);

    return n;
}

double getAverage(struct seaZone zone, int amZones, double allAverages[])
{
    double avg = 0;
    for (int i = 0; i < amZones; i++)
    {
        avg += allAverages[i];
    }

    avg /= amZones;

    return avg;
}

double getSmallest(double allAverages[], int amZones)
{
    double smallest = allAverages[0];

    for (int i = 0; i < amZones; i++)
    {
        if (smallest >= allAverages[i])
        {
            // printf("im running wee");
            smallest = allAverages[i];
        }
    }

    return smallest;
}

double getLargest(double allAverages[], int amZones)
{
    double largest = allAverages[0];

    for (int i = 0; i < amZones; i++)
    {
        if (largest <= allAverages[i])
        {
            // printf("im running wee");
            largest = allAverages[i];
        }
    }

    return largest;
}

int getIndex(double allAverages[], double numLookin, int amZones)
{
    for (int i = 0; i < amZones; i++)
    {
        if (allAverages[i] == numLookin)
        {
            return i;
        }
    }
}

double zoneVals(FILE *initFile, struct seaZone zone, int amZones, double allAverages[])
{
    int n = 0;
    double average = 0.0;
    double zoneAvg = 0;
    for (int z = 0; z < amZones; z++)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    fscanf(initFile, "%d", &n);
                    zone.vals[z][i][j][k] = n;
                    //printf("vals: %d \n", zone.vals[z][i][j][k]);
                    zoneAvg += zone.vals[z][i][j][k];
                }
            }
        }

        average += zoneAvg;
        allAverages[z] = (zoneAvg / 125.0);
        zone.average = allAverages[z]; 
        zoneAvg = 0;
    }

    // printf("allAverages: %lf %lf", allAverages[0], allAverages[1]);

    return average / (125 * amZones);
}


void normalizedZone(FILE *normalizedFile, FILE *initFile, double allAverages[], int amZones, struct seaZone zone, int numZone)
{
    int normalValue = 0; 
    int n; 
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    fscanf(initFile, "%d", &n);
                    zone.vals[numZone][i][j][k] = n;
                    //printf("vals: %d \n", zone.vals[z][i][j][k]);
                    if (normalValue > n)
                    {
                        normalValue = n; 
                    }  

                }
            }

        }

        //printf("normVal: %d \n", normalValue);

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    int normalizeAmount = zone.vals[numZone][i][j][k] + abs(normalValue);
                    fprintf(normalizedFile, "%d ", normalizeAmount);
                    //printf("%d he he he \n", normalizeAmount);
                }

                fprintf(normalizedFile, "\n");
            }
        }

        fprintf(normalizedFile, "\n");


}
    

int main(void)
{
    printf("Project 2 - Akshita Ramesh and Ziona Tucker \n \n");

    FILE *initFile, *normalizedFile;
    struct seaZone zone;
    double allAverages[1000];
    double aveg = 0;

    initFile = fopen("seaZone.dat", "r");
    normalizedFile = fopen("normalizedSeaData.dat", "w");

    int zoneSize = getVals(initFile);
    int numZones = getZones(initFile);

    printf("input file: seaZone.dat \n");
    printf("zone size : %dx%dx%d (%d cells) \n", zoneSize, zoneSize, zoneSize, (zoneSize * zoneSize * zoneSize));
    printf("# of zones: %d \n", numZones);

    aveg = zoneVals(initFile, zone, numZones, allAverages);

    printf("average   : %.3lf \n", aveg);

    double small = getSmallest(allAverages, numZones);
    // printf("val: %lf", small);
    int zoneNumsky = getIndex(allAverages, small, numZones);
    printf("smallest zone average : #%d (%lf) \n", zoneNumsky + 1, small);

    double large = getLargest(allAverages, numZones);
    // printf("val: %lf", large);
    int zoneNumskyTwo = getIndex(allAverages, large, numZones);
    printf("largest zone average  : #%d (%lf) \n", zoneNumskyTwo + 1, large);



    fclose(initFile);
    initFile = fopen("seaZone.dat", "r");

    zoneSize = getVals(initFile);
    numZones = getZones(initFile);

    fprintf(normalizedFile, "%d \n", zoneSize);
    fprintf(normalizedFile, "%d \n", numZones);

    for (int i = 0; i < numZones; i++)
    {
        normalizedZone(normalizedFile, initFile, allAverages, numZones, zone, i);
    }

    printf("normalized output file: normalizedSeaData.dat");


    fclose(initFile);
    fclose(normalizedFile);
    return 0;
}

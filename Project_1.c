#include <stdio.h>
#include <stdbool.h>  

/* Project 1
   Akshita Ramesh
    EGRE 246    */

double lowerLimit = 0, upperLimit = 0; 
int numTrapezoids = 0; 

double funct(double x); // function method
int getTrap(void); 
bool errorFound(void); 
bool errorFoundTwo(void);
double trap (double a, double b, int n);
double getLowLim ();
double getUpperLim ();
void execute (double lowerLimit, double upperLimit);



bool errorFound (void)
{
    if(upperLimit < lowerLimit)
    {
        printf("[ERROR]: the lower limit must be less than the upper limit; please try again \n");
        return true; 

    } 

    return false; 

}

bool errorFoundTwo (void) 
{
    
    if (numTrapezoids < 0)
    {
        printf("[ERROR]: the number of trapezoids must be greater than 0; please try again \n");
        return true; 
    } 

    return false; 
}

double trap (double a, double b, int n) 
{
    double val = (b - a)/ ((double) n);
    
    double answer = 0;

    for (int i = 1; i <= n ; i++)
    {
        double this = (val * (((funct(a + ((i - 1)*val)))) + (funct(a + (i*val))))) / 2;
        answer += this;
    }

    return answer; 

}

double getLowLim ()
{
    printf("lower limit: ");
    scanf("%lf", &lowerLimit);
    //printf("vals: %lf", lowerLimit);
    return lowerLimit; 
}

double getUpperLim ()
{
    printf("upper limit (should be greater than %0.2f): ", lowerLimit);
    scanf("%lf", &upperLimit);
    //printf("vals: %lf", upperLimit);
    return upperLimit; 
}

void execute (double lowerLimit, double upperLimit)
{
    lowerLimit = getLowLim();

    upperLimit = getUpperLim(); 
}

int getTrap (void)
{
    printf("number of trapezoids: ");
    scanf("%d", &numTrapezoids);
    return numTrapezoids; 
}

int main(void) 
{
     printf("EGRE 246 Project #1 Fall 2023 - Akshita Ramesh \n");

    execute(lowerLimit, upperLimit); 

    while (errorFound())
    {
        execute(lowerLimit, upperLimit); 
    }

    //printf("Values: lowerlimit: %lf, upperlimit: %lf, numTraps: %d", &lowerLimit, &upperLimit, numTrapezoids);
    // printf("vals: %lf", &numTrapezoids);     

    numTrapezoids = getTrap();

    while (errorFoundTwo())
    {
        numTrapezoids = getTrap();
        //printf("traps: %d", numTrapezoids);
    }


    if (!errorFound() && !errorFoundTwo())
    {
        //printf("Values: lowerlimit: %lf, upperlimit: %lf, numTraps: %d", lowerLimit, upperLimit, numTrapezoids);
        printf("value: %lf", trap(lowerLimit, upperLimit, numTrapezoids));
    } 

    return 0;

}

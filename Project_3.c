#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"
#ifdef NAN
#endif

/* Project 3
   Akshita Ramesh
   EGRE 246 - Fall 2023  */

complex newComplex(double realPart,double imagPart) 
{
    complex numsky = (complex) malloc(sizeof(int)); 
    numsky->real = realPart; 
    numsky->imag = imagPart; 

    return numsky;

}

void freeComplex(complex c)
{
    free(c); 
} // frees allocated complex number

double getReal(const complex c){
    
    return c->real; 
}// returns real part

double getImag(const complex c)
{
    return c->imag;
} // returns imaginary

void setReal(complex c,double n)
{
    c->real = n;    
} // sets real part

void setImag(complex c,double n)
{
    c->imag = n;
}// sets imaginary part

bool isReal(const complex c) 
{
    if (c->imag == NAN || c->imag == 0)
    {
        return true; 
    }
    
    return false; 
} // returns true if c is a real number, false

bool equal(const complex op1,const complex op2,double t) 
{
    // edit - subtract t but get absolute value (has to be within tolerance)
    
    double realdifference = 0;

    double imagdifference = 0;

    realdifference = fabs(op1->real) - fabs(op2->real);

    imagdifference = fabs(op1->imag) - fabs(op2->imag);

    if (realdifference >= t || imagdifference >= t)
    {
        return false;
    }

    else if (realdifference >= t && imagdifference >= t)
    {
        return false; 
    }

    return true; 
} // returns true if op1 == op2 within tolerance t

complex conjugate(const complex c) 
{
    double conj = c->imag * -1; 
    complex conjugate = newComplex(c->real, conj); 

    return conjugate;
    // - whats the point of this if there's a tostring?   
}// returns the conjugate of c

complex add(const complex c1, const complex c2)
{
    double realsies = 0.0;
    double imagsies = 0.0; 

    realsies = c1->real+ c2->real; 
    imagsies = c1->imag + c2->imag; 

    complex added = newComplex(realsies, imagsies); 

    return added; 
} // returns c1 + c2

complex sub(const complex c1, const complex c2)
{
    double realsies = 0.0;
    double imagsies = 0.0; 


    realsies = c1->real - c2->real; 
    imagsies = c1->imag - c2->imag; 

    
    //printf("word: %lf, word2: %lf", realsies, imagsies);
    complex subtracted = newComplex(realsies, imagsies); 

    return subtracted;
} // returns c1 - c2

complex mul(const complex c1, const complex c2) 
{
    double num1 = 0.0;
    double num2 = 0.0; 
    double num3 = 0.0; 
    double num4 = 0.0; 

    double real = (c1->real* c2->real) - (c1->imag * c2->imag); 
    double imaginary = (c1->imag * c2->real) + (c1->real * c2->imag);  

    // printf("word: %lf, word2: %lf \n", real, imaginary);
    complex multiplied = newComplex(real, imaginary); 

    return multiplied;
}// returns c1 * c2

complex divide(const complex c1, const complex c2)
{
    //double real = ((c1->real* c2->real)+(c1->imag * c2->imag)) / ((c2->real * c2->real) + (c2->imag * c2->imag));

    double imaginary = ((c1->imag * c2->real) - (c1->real * c2->imag)) / ((c2->real * c2->real) + (c2->imag * c2->imag)); 

    double real = ((c1->real * c2->real) + (c1->imag * c2->imag)) / ((c2->real * c2->real) + (c2->imag * c2->imag));
    
    
    complex divided = newComplex(real, imaginary); 
    //printf("yih: %lf, word: %lf, word2: %lf \n", real, imaginary);


    if (toString(c2, 0) == "0+0i")
    {
        divided->real = NAN; 
        divided->imag = NAN; 
    }

    return divided; 
}// returns c1 / c2

// division by 0+0i returns NAN+NANi

char *toString(const complex c,int p) 
{
    if (p < 0 || p > 15)
    {
        p = 6; 
    }

    // int size = (4 + p)
    char* str = (char*)malloc(1000);  
    //char realy[size] = c.real;
    //char fakey[size] = c.imag;

    if (c->imag < 0)
    {
       sprintf(str, "%.*lf%.*lfi", p, c->real, p, c->imag);  
    }

    else {
        sprintf(str, "%.*lf+%.*lfi", p, c->real, p, c->imag); 
    }
    

    return str;
}



/* int main(void) {

    complex c1 = newComplex(1.2399999,2.00099999),c2;
    printf("%s\n",toString(c1,0));
    printf("%s\n",toString(c1,2));
    printf("%s\n",toString(c1,5));
    freeComplex(c1);

    c1 = newComplex(3,4); c2 = newComplex(2,5);
    printf("%s + %s = %s\n",toString(c1,0),toString(c2,0),toString(add(c1,c2),0));
    freeComplex(c1); 
    return 0; 

    c1 = newComplex(3.4,16.3); c2 = newComplex(0.04112,0.06722);
    divide(c1, c2); 
    printf("\n");
    //printf("%s + %s = %s\n",toString(c1,0),toString(c2,0),toString(add(c1,c2),0));
    freeComplex(c1);

    //c1 = newComplex(3.4,16.3); c2 = newComplex(0.04112,0.06722);
    c1 = newComplex(0,-2); c2 = newComplex(0,-0.39);
    mul(c1, c2); 
    printf("\n");
    // printf("%s + %s = %s\n",toString(c1,0),toString(c2,0),toString(add(c1,c2),0));
    freeComplex(c1);
    return 0; 
} */ 




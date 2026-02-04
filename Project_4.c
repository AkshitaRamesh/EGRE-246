#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bint.h"

/* Project 4
   Akshita Ramesh
   EGRE 246 - Fall 2023  */

struct bintType {
    int array[MAX_SIZE]; // Array to store digits
    int sign;             // 1 for positive, -1 for negative
    int digits;             // Number of digits in the number
};

bint createBint() {
    bint num = (bint)malloc(sizeof(struct bintType));
    num->digits = 1;
    num->sign = 1;
    return num;
}

void destroyBint(bint b) {
    free(b);
}

void assignInt(bint b, long n) {
    if (n < 0) 
    {
        b->sign = -1;
        n = -n;
    } 
    else {
        b->sign = 1;
    }
    b->digits = 0;
    while (n > 0) {
        b->array[b->digits++] = n % 10;
        n /= 10;
    } 

    /* int loopy = n;
    int dig = 0;  
    while (loopy != 0)
    {
        loopy /= 10; 
        dig++; 
        
    } */ 

    //printf("dig: %d ", dig); 
    /* b->digits = dig;

    for (int i = 0; i < dig; i++)
    {
        b->array[i] = n % 10; 
        b->digits += 1;
        n /= 10;  
        //printf("%d", b->array[i]); 
    } */ 
}

void assignStr(bint b, char* s) {
    int lengthOfString = strlen(s);
    int start = 0;
    if (s[0] == '-') {
        b->sign = -1;
        start = 1;
    } else {
        b->sign = 1;
    }

    b->digits = lengthOfString - start;
    for (int i = start; i < lengthOfString; i++) {
        b->array[i - start] = s[lengthOfString - i - 1] - '0';
    }
}

void copy(const bint b1, bint b2) {
    b2->sign = b1->sign;
    b2->digits = b1->digits;
    for (int i = 0; i < b1->digits; i++) {
        b2->array[i] = b1->array[i];
    }
}

int cmp(const bint b1, const bint b2) {
    if (b1->sign < b2->sign)
    {   
        return -1;
    } 
    if (b1->sign > b2->sign) 
    {
        return 1;
    }
    if (b1->digits < b2->digits)
    {
        return -1;
    } 
    if (b1->digits > b2->digits)
    {
        return 1;
    } 

    for (int i = b1->digits - 1; i >= 0; i--) {
        if (b1->array[i] < b2->array[i]) 
        {
            return -1;
        }
        if (b1->array[i] > b2->array[i]) 
        {
            return 1;
        }
    }

    return 0;

    /* if (b1->posNeg < b2->posNeg)
    {
        return -1;
    } else if (b1->posNeg > b2->posNeg)
    {
        return 1;
    }

    if ((b1->posNeg + b2->posNeg) > 0)
    {
        if (b1->digits < b2->digits)
        {
            return -1; 
        } else if (b1->digits > b2->digits)
        {
            return 1; 
        } else {
            for (int i = b1->digits; i <= 0; i--)
            {
                if (b1->array[i] > b2->array[i])
                {
                    return 1; 
                } 
                else if (b1->array[i] < b2->array[i])
                {
                    return -1; 
                }
            }
        } 
        // going to be positive
        
    }

    if ((b1->posNeg + b2->posNeg) < 0)
    {
        if (b1->digits < b2->digits)
        {
            return 1; 
        } else if (b1->digits > b2->digits)
        {
            return -1; 
        } else {
            for (int i = b1->digits; i <= 0; i--)
            {
                if (b1->array[i] > b2->array[i])
                {
                    return -1; 
                } 
                else if (b1->array[i] < b2->array[i])
                {
                    return 1; 
                }
            }
        }

        
    } */ 
}

void absval(const bint b, bint res) {
    copy(b, res);
    res->sign = 1;
}

void add(const bint b1, const bint b2, bint res) {
    int carry = 0;
    int maxSize = 0; 
    
    if (b1->digits > b2->digits) 
    {
        maxSize = b1->digits;
    } else {
        maxSize = b2->digits;
    }

    for (int i = 0; i < maxSize; i++) {
        int sum = b1->array[i] + b2->array[i] + carry;
        res->array[i] = sum % 10;
        carry = sum / 10;
    }

    res->digits = maxSize;
    if (carry > 0) {
        res->array[maxSize] = carry;
        res->digits++;
    }

    if (b1->sign == b2->sign){
        res->sign = b1->sign;
    } else {
       res->sign = b2->sign;
    }
}

void sub(const bint b1, const bint b2, bint res) {
    if (b1->sign != b2->sign) {
        bint temp = createBint();
        absval(b2, temp);
        add(b1, temp, res);
        destroyBint(temp);
        return;
    }

    if (cmp(b1, b2) < 0) {
        sub(b2, b1, res);
        res->sign = -1;
        return;
    }

    int borrow = 0;
    for (int i = 0; i < b1->digits; i++) {
        int diff = b1->array[i] - b2->array[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res->array[i] = diff;
    }

    while (res->digits > 1 && res->array[res->digits - 1] == 0) {
        res->digits--;
    }

    res->sign = 1;
}

void mul(const bint b1, const bint b2, bint res) {
    bint numOne = createBint();
    bint numTwo = createBint();
    bint numThree = createBint();

    assignInt(res, 0);

    for (int i = 0; i < b2->digits; i++) {
        int carry = 0;

        for (int j = 0; j < b1->digits; j++) {
            int product = b1->array[j] * b2->array[i] + carry;
            numOne->array[j] = product % 10;
            carry = product / 10;
        }

        if (carry > 0) {
            numOne->array[b1->digits] = carry;
            numOne->digits = b1->digits + 1;
        } else {
            numOne->digits = b1->digits;
        }

        for (int k = 0; k < i; k++) {
            numOne->array[numOne->digits++] = 0;
        }

        add(res, numOne, numTwo);
        copy(numTwo, res);
    }

    if (b1->sign == b2->sign) {
    res->sign = 1;
    } else {
    res->sign = -1;
    }

}

void divide(const bint b1, const bint b2, bint res) {
       if (cmp(b2, createBint()) == 0) {
        printf("Error: Can't divide by 0");
        return; 
    }

    bint dividend = createBint();
    bint divisor = createBint();
    bint quotient = createBint();
    bint remainder = createBint();

    copy(b1, dividend);
    copy(b2, divisor);

    absval(dividend, dividend);
    absval(divisor, divisor);

    if (cmp(dividend, divisor) < 0) {
        assignInt(res, 0);
        return;
    }

    int shift = dividend->digits - divisor->digits;
    while (shift >= 0) {
        assignInt(quotient, 0);
        quotient->digits = shift + 1;
        quotient->array[shift] = 1;

        mul(divisor, quotient, remainder);

        while (cmp(dividend, remainder) >= 0) {
            sub(dividend, remainder, remainder);
            add(quotient, res, res);
        }

        shift--;

        assignInt(remainder, 0);
    }

    res->sign = (b1->sign == b2->sign) ? 1 : -1;
}

void rem(const bint b1, const bint b2, bint res) {
    bint quotient = createBint();
    divide(b1, b2, quotient);
    mul(b2, quotient, res);
    sub(b1, res, res);
}

bool isPos(const bint b) {
    return (b->sign == 1);
}

int getSize(bint b) {
    return b->digits;
}

char* toString(const bint b) {
    int strSize = b->digits + 1;
    char* str = (char*)malloc(strSize);

    int index = 0;
    if (b->sign == -1) {
        str[index++] = '-';
    }

    for (int i = b->digits - 1; i >= 0; i--) {
        str[index++] = b->array[i] + '0';
    }

    str[index] = '\0';
    return str;

    /* for (int i = b->digits; i >= 0; i--)
    {
        //int* add = (int*) b->array[i]; 
        // sprintf(stringy[i], "%d", b->array[i]);
        //printf("%d", b->array[i]);
        int add = b->array[i];
        sprintf(ch, "%d", add);



        printf("%c", ch); 
        //printf("running");
    } */ 
}

bool didExtraCredit() {
    return true; // You've implemented all 5 arithmetic functions
}

/* int main(void) {
  bint b1 = createBint(),b2 = createBint(),
    res = createBint();


  assignInt(b1,2);
  assignStr(b1,"hi");
  copy(b1,b2);
  cmp(b1,b2);
  absval(b1,b2);
  add(b1,b2,res);
  sub(b1,b2,res);
  mul(b1,b2,res);
  divide(b1,b2,res);
  rem(b1,b2,res);
  isPos(b1);
  getSize(b1);
  toString(b1);
  printf("did extra credit? %s\n",
         didExtraCredit()?"yes":"no"); 
  destroyBint(b1);
  printf("=== if there are no errors reported your code compiled & ran ok ===\n");
  return 0;
} */




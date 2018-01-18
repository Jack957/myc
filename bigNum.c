#include <stdio.h> 
#include <stdlib.h>

#define N 8

void add(int*, int*, int*);
void subtract(int*, int*, int*);
void multiply(int*, int, int*);
void divide(int*, int, int*);
void toComp(int*, int*);  // 轉補數
void absv(int*, int*);    // 轉絕對值
void print(int*);         // 顯示大整數


int main(void) { 
    int a[] = {0, 0, 0, 1234, 5678, 9910, 1923, 1124};
    int b[] = {9999, 9999, 9999, 9999, 9999, 9999, 9999, 9901}; // -99
    int c1[N], c2[N], c3[N], c4[N] = {0};
    
    printf("a = "); print(a);
    printf("b = "); print(b);
        
    add(a, b, c1);      printf("a +  b = ");     print(c1);
    subtract(a, b, c2); printf("a -  b = ");     print(c2);
    multiply(a, -3, c3);printf("a * -3 = ");     print(c3);
    divide(a, -3, c4);  printf("a / -3 = ");     print(c4);

    return 0; 
} 

void add(int* a, int* b, int* c) { 
    if(b[0] == 9999) {
        int comp[N] = {0};
        toComp(b, comp);
        subtract(a, comp, c);
    } else {
        int i, carry = 0; 
        for(i = N - 1; i >= 0; i--) {
            c[i] = a[i] + b[i] + carry; 
            if(c[i] < 10000) {
                carry = 0; 
            } else { // 進位 
                c[i] = c[i] - 10000; 
                carry = 1; 
            } 
        } 
    }
} 

void subtract(int* a, int* b, int* c) {
    if(b[0] == 9999) {
        int comp[N] = {0};
        toComp(b, comp);
        add(a, comp, c);
    } else {
        int i, borrow = 0; 
        for(i = N - 1; i >= 0; i--) { 
            c[i] = a[i] - b[i] - borrow; 
            if(c[i] >= 0) {
                borrow = 0;
            } else { // 借位 
                c[i] = c[i] + 10000; 
                borrow = 1; 
            } 
       } 
    }
} 

void multiply(int* a, int b, int* c) { // b 為乘數
    int op1[N] = {0}; absv(a, op1);
    int op2 = abs(b);

    int i, tmp, carry = 0; 
    for(i = N - 1; i >= 0; i--) { 
        tmp = op1[i] * op2 + carry; 
        c[i] = tmp % 10000;    
        carry = tmp / 10000; 
    }
    
    if((a[0] == 9999 && b > 0) || (a[0] == 0 && b < 0)) {
        toComp(c, c);
    }
} 

void divide(int* a, int b, int *c) {  // b 為除數 
    int op1[N] = {0}; absv(a, op1);
    int op2 = abs(b);
    
    int i, tmp, remain = 0; 
    for(i = 1; i < N; i++) { 
        tmp = op1[i] + remain; 
        c[i] = tmp / op2; 
        remain = (tmp % op2) * 10000; 
    }

    if((a[0] == 9999 && b > 0) || (a[0] == 0 && b < 0)) {
        toComp(c, c);
    }    
}

void toComp(int* src, int* comp) {
    int j;
    for(j = 0; j < N; j++) {
        comp[j] = 9999 - src[j];
    }
    comp[N - 1] += 1;
}

void absv(int* src, int* op) {
    if(src[0] == 9999) {
        toComp(src, op);
    } else {
        int i;
        for(i = 0; i < N; i++) {
            op[i] = src[i];
        }
    }
}

void print(int* c) {
    int v[N] = {0}; absv(c, v);
    
    if(c[0] == 9999) {
        printf("-");
    }
    
    int isDropZero = 1;
    int i;
    for(i = 0; i < N; i++) {
        char s[5] = {'\0'};
        sprintf(s, "%04d", v[i]);
        if(isDropZero) {
            int j;
            for(j = 0; s[j] == '0' && j < 4; j++);
            if(j < 4) {
                isDropZero = 0;
                for(; j < 4; j++) {
                    printf("%c", s[j]);
                }
            } else if(i == N - 1) {
                printf("0");
            }
        } else {
            printf(s);
        }
    }
    printf("\n");
}
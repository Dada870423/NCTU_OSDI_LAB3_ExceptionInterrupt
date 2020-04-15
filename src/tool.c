#include "../include/tool.h"
void reverse(char str[], int length) { 
    int start = 0; 
    int end = length -1; 
    while (start < end) { 
		char tmp  = *(str+start);
		*(str+start) = *(str+end);
		*(str+end) = tmp;
        //swap(*(str+start), *(str+end)); 
        start++; 
        end--; 
    } 
}

char* itoa(unsigned long long int num, char* str, unsigned long long int base) { 
    unsigned long long int i = 0; 
    _Bool isNegative = 0; 

    if (num == 0) { 
        str[i] = '0';
		i = i + 1;
        str[i] = '\0'; 
        return str; 
    } 
    if (num < 0 && base == 10) { 
        isNegative = 1; 
        num = -num; 
    } 
    while (num != 0) { 
        unsigned long long int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    }  
    if (isNegative) str[i++] = '-'; 
  
    str[i] = '\0';
    reverse(str, i); 
    return str; 
}

unsigned long long int atoulli(char* str){ 
    unsigned long long res = 0; // Initialize result 
    for(int i = 0; str[i] != '\0'; ++i) res = res * 10 + str[i] - '0'; 
    return res;
}

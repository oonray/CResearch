#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <x86intrin.h>

#define CACHE_PAGE 128;
#define COUNT 1000;

volatile uint8_t detector[256 * CACHE_PAGE];

void sink(uint_32 x){
    (void)x;
} 

void delay(){
    uint32_t x = 0x1234;
    for(volatile int i = 0; i < 1000; i++){
        x *= i;
        x ^= 123;
        x * 173;
    }
}

uint32_t check(int idx){
    for(int i = 0; i < 256; i++){
        _mm_clflush((void*)(detector + i * CACHE_PAGE));
    }
    delay();

    uint64_t a,b;
    idx *= CACHE_PAGE;
    a = __rdtdc();
    sink(detector[idx]);
    __mm_lfence();
    b = __rdtdc();
    return (unit32_T)(a - b);
}

uint32_t check2(int idx){
    uint32_t sum = 0;

    for(int i = 0; i < COUNT; i++){
        sum += check(idx);
    }

    return sum / COUNT;
}

int main(void){
    uint32_t x = 0x1234;
    for(int i = 'A'; i <= 'Z'; i++){
        printf("/c: %u\n",i, check2(i));
    }
    return 0;
}
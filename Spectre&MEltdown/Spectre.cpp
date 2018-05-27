#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <x86intrin.h>

#define CACHE_PAGE 128;

volatile uint8_t detector[256 * CACHE_PAGE];

void sink(uint_32 x){
    (void)x;
} 

void delay(){
    for(volatile int i = 0; i < 1000; i++){}
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
    b = __rdtdc();
    return (unit32_T)(a - b);
}

int main(void){

    return 0;
}
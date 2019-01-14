#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint16_t memory[UINT16_MAX];
uint16_t reg[R_COUNT];

//Registers
enum{ R_R0 = 0, R_R1, R_R2, R_R3, R_R4, R_R5, R_R6, R_R7, R_PC, R_COND, R_COUNT };

//OP Codes | Isntruction set
enum
{
    OP_BR = 0,      // branch 
    OP_ADD,         // add  
    OP_LD,          // load 
    OP_ST,          // store 
    OP_JSR,         // jump register 
    OP_AND,         // bitwise and 
    OP_LDR,         // load register 
    OP_STR,         // store register 
    OP_RTI,         // unused 
    OP_NOT,         // bitwise not 
    OP_LDI,         // load indirect 
    OP_STI,         // store indirect 
    OP_JMP,         // jump 
    OP_RES,         // reserved (unused) 
    OP_LEA,         // load effective address 
    OP_TRAP         // execute trap 
};

//Condition Flags
enum
{
    FL_POS = 1 << 0,    // Position 
    FL_ZRO = 1 << 1,    // Zero
    FL_NEG = 1 << 2,    // Negative
};

int main(int argc, char *argv[]){

    enum {START = 0x3000};
    reg[R_PC] = START;


    int running = 1;
    
    
}
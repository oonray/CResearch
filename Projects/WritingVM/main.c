#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

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

uint16_t sign_extend(uint16_t x, int bit_count)
{
    if ((x >> (bit_count - 1)) & 1) {
        x |= (0xFFFF << bit_count);
    }
    return x;
}

void update_flags(uint16_t r)
{
    if (reg[r] == 0)
    {
        reg[R_COND] = FL_ZRO;
    }
    else if (reg[r] >> 15) 
    {
        reg[R_COND] = FL_NEG;
    }
    else
    {
        reg[R_COND] = FL_POS;
    }
}


int main(int argc, char *argv[]){

    enum {START = 0x3000};
    reg[R_PC] = START;


    int running = 1;

    while(running){
        uint16_t intstr = memread(reg[R_PC]++);
        uint16_t op = intstr >> 12;

        switch(op){
            case OP_ADD:
            {
                /* destination register (DR) */
                uint16_t r0 = (instr >> 9) & 0x7;
                /* first operand (SR1) */
                uint16_t r1 = (instr >> 6) & 0x7;
                /* whether we are in immediate mode */
                uint16_t imm_flag = (instr >> 5) & 0x1;

                if (imm_flag)
                {
                    uint16_t imm5 = sign_extend(instr & 0x1F, 5);
                    reg[r0] = reg[r1] + imm5;
                }
                else
                {
                    uint16_t r2 = instr & 0x7;
                    reg[r0] = reg[r1] + reg[r2];
                }

                update_flags(r0);
            }
                break;        
            case OP_AND:
                break;
            case OP_NOT:
                break;
            case OP_BR:
                break;
            case OP_JMP:
                break;
            case OP_JSR:
                break;
            case OP_LD:
                break;
            case OP_LDI:
                break;
            case OP_LDR:
                break;
            case OP_LEA:
                break;
            case OP_ST:
                break;
            case OP_STI:
                break;
            case OP_STR:
                break;
            case OP_TRAP:
                break;
            case OP_RES:
            case OP_RTI:
            default:
                break;      
        }

    }
    
    
}
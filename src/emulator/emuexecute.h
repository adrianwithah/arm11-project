#ifndef EMUEXECUTE_H
#define EMUEXECUTE_H

#include"emustruct.h"
#include<assert.h>
#define CPSR_BIT_LOWER 28
#define CPSR_BIT_UPPER 31
#define SHIFT_GAP_NZCV_CPSR 28
#include"alu.h"
#include"shifter.h"



/*helper functinos*/
uint32_t calculate_imm(Instruction_t *ins, int32_t *reg);
uint32_t executable(Instruction_t *ins, int32_t *cpsr);

void execute_data_processing(Instruction_t *ins, Storage_t *storage);
void execute_multiply(Instruction_t *ins, Storage_t *storage);
void execute_single_data_transfer(Instruction_t *ins, Storage_t *storage);
void execute_branch(Instruction_t *ins, Storage_t *storage);

#endif


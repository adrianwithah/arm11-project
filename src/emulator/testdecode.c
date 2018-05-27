
#include"pipeline.h"
#include"emustruct.h"
#include"emudef.h"
typedef uint32_t U;
#define SIZE 1000

void check_value_range(Instruction_t *ins) {
	assert(ins->cond <= (1<<4) -1);
	assert(ins->n <= 1);
	assert(ins->z <= 1);
	assert(ins->c <= 1);
	assert(ins->v <= 1);
	assert(ins->i <= 1);
	assert(ins->s <= 1);
	assert(ins->opcode <= (1<<4)-1);
	assert(ins->rn <= (1<<4)-1);
	assert(ins->rd <= (1<<4)-1);
	assert(ins->rs <= (1<<4)-1);
	assert(ins->rm <= (1<<4)-1);
	assert(ins->rotate <= (1<<4)-1);

	switch(ins->instruction_type) {
		case SINGLE_DATA_TRANSFER:
			assert(ins->imm <= (1<<12)-1);
			break;
		default:
			assert(ins->imm <= (1<<8)-1);
	}
	assert(ins->shift_type <= (1<<2)-1);
	assert(ins->shift_constant <= (1<<5)-1);
	assert(ins->a <= 1);
	assert(ins->p <= 1);
	assert(ins->u <= 1);
	assert(ins->l <= 1);
	assert(ins->o <= 1);
	assert(ins->address <= (1 << 24) - 1);
}

int main(void) {
	U original_code;
	U i = 0;
	while(i++ < SIZE) {
		original_code = rand();
		Instruction_t *ins = new_instruction();
		ins->binary_code = original_code;
		ins->isFetched = 1;
		decode(ins);
		check_value_range(ins);
	}
}

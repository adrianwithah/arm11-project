#include<stdio.h>
#include<stdint.h>
#include<assert.h>
#include<stdlib.h>
#include"emustruct.h"
#include"emuio.h"
#define INSTRUCTION_LENGTH 32
#define BYTES_FOR_INT 4
#define ZERO '0'
#define ONE '1'
uint32_t *convert(char *buffer, size_t *size);

uint32_t *emuread(char *fileName, size_t *size) {

    FILE *file;

    char *buffer;
    unsigned long lengthFile;

    file = fopen(fileName, "rb");

    assert(file != NULL);

    if (!file) {
        fprintf(stderr, "Unable to open file %s", fileName);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    lengthFile = (unsigned long) ftell(file);

    fseek(file, 0, SEEK_SET);

    buffer = (char *) malloc(lengthFile + 1);

    assert(buffer != NULL);

    if (!buffer) {
        fprintf(stderr, "Memory error!");
        fclose(file);
        return NULL;
    }

    fread(buffer, lengthFile, 1, file);
    fclose(file);

  
    uint32_t *address = convert(buffer, size);

    free(buffer);
    return address;
}

uint32_t *convert(char *buffer, size_t *size) {
    int x = 0;
    int y = 0;
	*size = 1;

	while(buffer[y]) {
		*size += (buffer[y] == '\n');
		y ++;
	}


	uint32_t *address = calloc(*size, sizeof(uint32_t));
	
	y = 0;
	int line_length = 0;
	int decimal = 0;
	int power = INSTRUCTION_LENGTH - 1;
    while (buffer[y]) {
		if (buffer[y] == '\n') {
			assert(line_length == INSTRUCTION_LENGTH);
			address[x] = decimal;
			x++;
			decimal = 0;
			power = INSTRUCTION_LENGTH - 1;
			line_length = 0;
			y++;
			continue;
		}
		line_length++;
		assert(buffer[y] == ZERO || buffer[y] == ONE);
        assert(line_length <= INSTRUCTION_LENGTH);
		if (buffer[y] == ONE) {
        	decimal += powerOfTwo(power);
        }
        y++;
        power--;
    }

    return address;
}

void emuwrite(Storage_t *storage) {

    assert(storage != NULL);

    printf("Registers:\n");

    for (int i = 0; i < 13; i++) {
        printf("$%-3d", i);
        printf(": %10d (0x%08x)\n", storage->reg[i], storage->reg[i]);
    }

    printf("PC");
    printf(": %10d (0x%08x)\n", storage->reg[PC_REG], storage->reg[PC_REG]);

//  PART I: initialize the CPSR to 0
    printf("CPSR");
    printf(": %10d (0x%08x)\n", storage->reg[CPSR_REG], storage->reg[CPSR_REG]);

    printf("Non-zero memory location: \n");
    for (int i = 0; i < MEMORY_SIZE; i += BYTES_FOR_INT) {
        if (((int *) storage->mem)[i / BYTES_FOR_INT] != 0) {
            printf("0x%08x: 0x", i);
            for (int j = 0; j < BYTES_FOR_INT; j++) {
                printf("%02x", storage->mem[i + j]);
            }
            printf("\n");
        }
    }
}


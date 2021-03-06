#include<stdio.h>
#include<stdint.h>
#include<assert.h>
#include<stdlib.h>
#include"arm11struct.h"
#include"arm11io.h"


void emu_read(char *fileName, State_t *state) {
  FILE *file;
  size_t lengthFile;
  file = fopen(fileName, "rb");
  assert(file != NULL);
  if (!file) {
    fprintf(stderr, "Unable to open file %s", fileName);
    return;
  }

  fseek(file, 0, SEEK_END);
  lengthFile = (unsigned long) ftell(file);
  fseek(file, 0, SEEK_SET);

  //printf("length of file is %ld\n", lengthFile);
  size_t size = lengthFile/INSTRUCTION_BYTE;
  assert(size <= MEMORY_SIZE);
  state->instructions_size = size;

  for (int i = 0; i < size; i++) {
    fread(state->storage->mem+i, sizeof(uint32_t),1,file);
  }

  fclose(file);
  return;
}

void emu_write(Storage_t *storage) {
  assert(storage != NULL);
  printf("Registers:\n");
  for (int i = 0; i < 13; i++) {
    printf("$%-3d", i);
    printf(": %10d (0x%08x)\n", storage->reg[i], storage->reg[i]);
  }
  printf("PC  ");
  printf(": %10d (0x%08x)\n", storage->reg[PC_REG], storage->reg[PC_REG]);

//  PART I: initialize the CPSR to 0
  printf("CPSR");
  printf(": %10d (0x%08x)\n", storage->reg[CPSR_REG], storage->reg[CPSR_REG]);
  printf("Non-zero memory:\n");
  for (int i = 0; i < MEMORY_SIZE; i ++) {
    if ( *(storage->mem + i) != 0) {
    uint32_t value = *(storage->mem+i);
    uint32_t t = 4;
    printf("0x%08x: 0x", i*4);;
    while(t--) {
      printf("%02x", value & ((1<<8) - 1));
      value >>= 8;
    }
    printf("\n");
    }
  }
}

FILE* ass_read(char *path) {
  FILE* fp = fopen(path, "r");
  if(fp == NULL) {
    perror("Error opening file.\n");
    exit(EXIT_FAILURE);
  }

  return fp;
}

int ass_write(char* outFile, uint32_t* binTable, uint32_t noInst) {
  FILE* fp = fopen(outFile, "wb");
  if (fp == NULL) {
    perror("No such file");
    exit(EXIT_FAILURE);
  }

  fwrite(binTable, sizeof(uint32_t), noInst, fp);
  fclose(fp);
  return 0;
}

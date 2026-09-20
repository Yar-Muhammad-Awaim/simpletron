#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIMPLETRON_MEMORY_SIZE 100

int load_sml(const char *filename, int memory[SIMPLETRON_MEMORY_SIZE]) {
  if (filename == NULL || memory == NULL) {
    fprintf(stderr, "load_sml: NULL arguments\n");
    return -1;
  }

  char buffer[64];
  FILE *fptr;
  fptr = fopen(filename, "r");

  if (fptr == NULL) {
    fprintf(stderr, "load_sml: can't open file %s: %s", filename,
            strerror(errno));
    return -1;
  }

  for (int i = 0; i < SIMPLETRON_MEMORY_SIZE; i++) {
    memory[i] = 0;
  }

  int instruction_counter = 0;
  while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
    int value = (int)strtol(buffer, NULL, 10);
    memory[instruction_counter] = value;
    instruction_counter++;
  }

  for (int i = 0; i < SIMPLETRON_MEMORY_SIZE; ++i) {
    printf("%d\n", memory[i]);
  }
  fclose(fptr);
  return 0;
}

void dump_memory(int accumulator, int instruction_counter,
                 int instruction_register, int operation_code, int operand,
                 int memory[]) {
  printf("Accumulator: %+05d\n", accumulator);
  printf("Instruction Counter: %+05d\n", instruction_counter);
  printf("Instruction Register: %+05d\n", instruction_register);
  printf("Operation Code: %+05d\n", operation_code);
  printf("Operand: %+05d\n", operand);

  // this draws the first line
  for (int i = 1; i < 10; ++i) {
    if (i == 0) {
      printf(" ");
    } else {
      printf("\t%d", i);
    }
  }
  printf("\n");
  int line_number = 0;
  int memory_index = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == 0) {
        printf("%d\t", line_number);
        ++line_number;
      } else {
        printf("%+05d\t", memory[memory_index]);
        ++memory_index;
      }
    }
    printf("\n");
  }
  printf("\n");
  return;
}
/*
int main(void) {
  char filename[256];

  printf("Enter the filename => ");
  scanf("%255s", filename);

  int memory[100];

  for (int i = 0; i < 100; i++) {
    memory[i] = 0;
  }

  load_sml(filename, memory);

  return 0;
}
*/

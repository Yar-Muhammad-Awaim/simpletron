#include "simple.h"
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#define SIMPLETRON_MEMORY_SIZE 100

int load_sml(char *filename, int memory[100]);
void dump_memory(int accumulator, int instruction_counter,
                 int instruction_register, int operation_code, int operand,
                 int memory[]);

static int execute_program(int memory[]) {
  int accumulator = 0;
  int instruction_counter = 0;
  int instruction_register = 0;
  int running = 1;
  int operation_code = 0;
  int operand = 0;
  int result = 0;
  bool has_branched = false;

  while (running) {
    if (instruction_counter < 0 || instruction_counter >= 100) {
      fprintf(stderr, "Invaild Instruction Counter %d", instruction_counter);
      return -1;
    }

    // fetch the instrucction
    if (!has_branched) {
      instruction_register = memory[instruction_counter];
    }

    // check if the instruction is valid
    if (instruction_register < 0 || instruction_register > 9999) {
      fprintf(stderr, "Invalid instruction for simpletron %+05d",
              instruction_register);
      return -1;
    }

    operation_code = instruction_register / 100;
    operand = instruction_register % 100;

    if (operand < 0 || operand > SIMPLETRON_MEMORY_SIZE) {
      fprintf(stderr, "Invalid Operand: Pointing to memory %+05d", operand);
      return -1;
    }

    switch (operation_code) {
    case READ: {
      printf("Enter a number: ");
      scanf("%d", &result);

      if (result < -9999 || result > 9999) {
        fprintf(
            stderr,
            "The value to be stored is not in the range of -9999 and 9999 (%d)",
            result);
        break;
      }

      memory[operand] = result;
      ++instruction_counter;
      break;
    }
    case WRITE: {
      printf("%+05d", memory[operand]);
      ++instruction_counter;
      break;
    case LOAD:
      accumulator = memory[operand];
      ++instruction_counter;
      break;
    case STORE:
      memory[operand] = accumulator;
      ++instruction_counter;
      break;
    }
    case ADD: {
      result = accumulator + memory[operand];
      if (result < 0 || result > 9999) {
        fprintf(stderr,
                "Out of range value for accumulator in ADD operation: %+05d",
                result);
        break;
      }
      accumulator = (int)result;
      ++instruction_counter;
      break;
    }
    case SUBTRACT: {
      result = accumulator - memory[operand];
      if (result < 0 || result > 9999) {
        fprintf(
            stderr,
            "Out of range value for accumulator in SUBTRACT operation: %+05d",
            result);
        break;
      }
      accumulator = result;
      ++instruction_counter;
      break;
    }
    case DIVIDE: {
      result = (int)accumulator / memory[operand];
      if (result < 0 || result > 9999) {
        fprintf(stderr,
                "Out of range value for accumulator in DIVIDE operation: %+05d",
                result);
        break;
      }
      accumulator = result;
      ++instruction_register;
      break;
    }
    case MULTIPLY: {
      result = accumulator * memory[operand];

      if (result < 0 || result > 9999) {
        fprintf(stderr,
                "Out of range value for accumulator in DIVIDE operation: %+05d",
                result);
        break;
      }
      accumulator = result;
      ++instruction_counter;
      break;
    }
    case BRANCH: {
      instruction_register = operand;
      has_branched = true;
      break;
    }
    case BRANCHNEG: {
      if (accumulator < 0) {
        instruction_register = operand;
        has_branched = true;
      } else {
        ++instruction_register;
      }
      break;
    }
    case BRANCHZERO: {
      if (accumulator == 0) {
        instruction_register = operand;
        has_branched = true;
      } else {
        ++instruction_counter;
      }
      break;
    }
    case HALT: {
      fprintf(stdout, "SIMPLETRON Execution Successful.");
      running = 0;
      break;
    }
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "simple.c:main filename for sml program wasn't provided.");
    return -1;
  }

  char *filename = argv[1];
  int simpletron_memory[SIMPLETRON_MEMORY_SIZE];

  load_sml(filename, simpletron_memory);

  execute_program(simpletron_memory);
  return 0;
}

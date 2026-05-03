#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include "register_file.h"

/*
 * Check https://gbdev.io/gb-opcodes/optables/ and https://gist.github.com/SakiiR/62661e45ee8b2ab13f0dc8203a7dfbd9
 *
 */

typedef enum target {
    A, B, C, D, E, H, L, HL, BC, DE, SP
} target;

typedef enum instruction {
    ADD, ADDHL
} instruction;

void process_instruction(gb_register_file* register_file, instruction instruction, target target);

void process_instruction_add(gb_register_file *register_file, target target);
void process_instruction_addhl(gb_register_file *register_file, target target);

void process_sum_to_reg_a(gb_register_file *register_file, uint8_t value);
void process_sum_to_reg_hl(gb_register_file *register_file, uint16_t value);

#endif

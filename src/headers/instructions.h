#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include "register_file.h"

/*
 * Check https://gbdev.io/gb-opcodes/optables/ https://gist.github.com/SakiiR/62661e45ee8b2ab13f0dc8203a7dfbd9  https://rgbds.gbdev.io/docs/v1.0.1/gbz80.7#ADC_A,r8
 *
 */

typedef enum instruction {
    ADC_R8, ADC_HL, ADC_N8,
    ADD_R8, ADD_HL, ADD_N8, ADD_SP,
    AND_R8,
    LD
} instruction;

// variadic func
void process_instruction(gb_register_file* register_file, instruction instruction, ...);

void process_instruction_adc_r8(gb_register_file *register_file, target target);
void process_instruction_adc_hl(gb_register_file *register_file);
void process_instruction_adc_n8(gb_register_file *register_file, uint8_t value);

void process_instruction_add(gb_register_file *register_file, target target);
void process_instruction_add_hl(gb_register_file *register_file, target target);
void process_instruction_add_n8(gb_register_file *register_file, uint8_t value);
void process_instruction_add_sp(gb_register_file *register_file, int8_t value);

void process_instruction_and_r8(gb_register_file *register_file, target target);
void process_instruction_and_hl(gb_register_file *register_file);
void process_instruction_and_n8(gb_register_file *register_file, uint8_t value);

void process_instruction_ld_const(gb_register_file *register_file, target target, uint8_t value);
void process_instruction_ld_reg(gb_register_file *register_file, target target_reg, target source_reg);

void process_sum_to_reg_a(gb_register_file *register_file, uint8_t value);
void process_sum_to_reg_hl(gb_register_file *register_file, uint16_t value);

#endif

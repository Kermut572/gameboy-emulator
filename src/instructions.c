#include "headers/instructions.h"
#include "headers/register_file.h"
#include <stdint.h>
#include <stdlib.h>

void process_instruction(gb_register_file* register_file, instruction instruction, target target)
{
    switch (instruction) {
        case ADD:
            process_instruction_add(register_file, target);
            return;
        default:
            return;
    }
}

void process_instruction_add(gb_register_file *register_file, target target)
{
    switch (target) {
        case A:
            {}
            uint8_t a_val = register_file->a;
            process_sum_to_reg_a(register_file, a_val);
            return;
        case B:
            {}
            uint8_t b_val = register_file->b;
            process_sum_to_reg_a(register_file, b_val);
            return;
        case C:
            {}
            uint8_t c_val = register_file->c;
            process_sum_to_reg_a(register_file, c_val);
            return;
        case D:
            {}
            uint8_t d_val = register_file->d;
            process_sum_to_reg_a(register_file, d_val);
            return;
        case E:
            {}
            uint8_t e_val = register_file->e;
            process_sum_to_reg_a(register_file, e_val);
            return;
        case H:
            {}
            uint8_t h_val = register_file->h;
            process_sum_to_reg_a(register_file, h_val);
            return;
        case L:
            {}
            uint8_t l_val = register_file->l;
            process_sum_to_reg_a(register_file, l_val);
            return;
        case HL:
            {}
            uint8_t hl_val = (uint8_t) get_hl_register_value(register_file);
            process_sum_to_reg_a(register_file, hl_val);
            return;
        default:
            return;
    }
}

void process_instruction_addhl(gb_register_file *register_file, target target)
{
    switch (target) {
        case BC:
            {}
            uint8_t a_val = register_file->a;
            process_sum_to_reg_hl(register_file, a_val);
            return;
        case DE:
            {}
            uint8_t b_val = register_file->b;
            process_sum_to_reg_hl(register_file, b_val);
            return;
        case HL:
            {}
            uint8_t c_val = register_file->c;
            process_sum_to_reg_hl(register_file, c_val);
            return;
        case SP:
            {}
            uint8_t d_val = register_file->d;
            process_sum_to_reg_hl(register_file, d_val);
            return;
        default:
            return;
    }
}

void process_sum_to_reg_a(gb_register_file *register_file, uint8_t value)
{
    set_half_carry_flag(register_file, (register_file->a & 0xF) + (value & 0xF) > 0xF);
    bool overflow = __builtin_add_overflow(register_file->a, value, &register_file->a);
    set_carry_flag(register_file, overflow);
    set_zero_flag(register_file, register_file->a == 0);
    set_substraction_flag(register_file, false);
}

void process_sum_to_reg_hl(gb_register_file *register_file, uint16_t value)
{
    uint16_t hl_value = get_hl_register_value(register_file);
    set_half_carry_flag(register_file, (hl_value & 0xFF) + (value & 0xFF) > 0xFF);

    uint16_t* tmp = malloc(sizeof(uint16_t));
    if(!tmp) return;

    bool overflow = __builtin_add_overflow(hl_value, value, tmp);
    set_hl_register(register_file, *tmp);
    free(tmp);

    uint16_t new_hl_value = get_hl_register_value(register_file);

    set_carry_flag(register_file, overflow);
    set_zero_flag(register_file, new_hl_value == 0);
    set_substraction_flag(register_file, false);
}

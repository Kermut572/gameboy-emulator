#include "headers/instructions.h"
#include "headers/register_file.h"
#include "headers/stack.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

void process_instruction(gb_register_file* register_file, instruction instruction, ...)
{
    va_list args;
    va_start(args, instruction);
    switch (instruction) {
        case ADC_R8:
            {}
            target adc_r8 = va_arg(args, target);
            process_instruction_adc_r8(register_file, adc_r8);
            break;
        case ADC_HL:
            process_instruction_adc_hl(register_file);
            break;
        case ADC_N8:
            {}
            uint8_t adc_n8 = va_arg(args, int);
            process_instruction_adc_n8(register_file, adc_n8);
            break;
        case ADD_R8:
            {}
            target add_r8 = va_arg(args, target);
            process_instruction_add(register_file, add_r8);
            break;
        case ADD_HL:
            {}
            target add_hl = va_arg(args, target);
            process_instruction_add_hl(register_file, add_hl);
            break;
        case ADD_N8:
            {}
            uint8_t add_n8 = va_arg(args, int);
            process_instruction_add_n8(register_file, add_n8);
            break;
        case ADD_SP:
            {}
            int8_t add_sp = va_arg(args, int);
            process_instruction_add_sp(register_file, add_sp);
        case AND_R8:
            {}
            target and_r8 = va_arg(args, target);
            process_instruction_and_r8(register_file, and_r8);
        case LD:
            {}
            uint8_t value = va_arg(args, int);
            //process_instruction_ld(register_file, target, value);
            break;
        default:
            break;
    }
    va_end(args);
}

void process_instruction_adc_r8(gb_register_file *register_file, target target)
{
    uint8_t* reg_ptr = get_reg_pointer(register_file, target);
    if(!reg_ptr) return;

    process_sum_to_reg_a(register_file, *reg_ptr);
    bool carry_flag = get_carry_flag(register_file);
    process_sum_to_reg_a(register_file, (uint8_t) carry_flag); //is this legal?
}

void process_instruction_adc_hl(gb_register_file *register_file)
{
    process_sum_to_reg_a(register_file, (uint8_t) get_hl_register_value(register_file));
    bool carry_flag = get_carry_flag(register_file);
    process_sum_to_reg_a(register_file, (uint8_t) carry_flag);
}

void process_instruction_adc_n8(gb_register_file *register_file, uint8_t value)
{
    process_sum_to_reg_a(register_file, value);
    bool carry_flag = get_carry_flag(register_file);
    process_sum_to_reg_a(register_file, (uint8_t) carry_flag);
}

void process_instruction_add(gb_register_file *register_file, target target)
{
    uint8_t* reg_ptr = get_reg_pointer(register_file, target);
    if(reg_ptr){
        process_sum_to_reg_a(register_file, *reg_ptr);
        return;
    }

    process_sum_to_reg_a(register_file, (uint8_t) get_hl_register_value(register_file));
}

void process_instruction_add_hl(gb_register_file *register_file, target target)
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

void process_instruction_add_n8(gb_register_file *register_file, uint8_t value)
{
    process_sum_to_reg_a(register_file, value);
}

void process_instruction_add_sp(gb_register_file *register_file, int8_t value)
{
    set_half_carry_flag(register_file, (register_file->sp & 0xF) + (value & 0xF) > 0xF);
    bool overflow = __builtin_add_overflow(register_file->sp, value, &register_file->sp);
    set_carry_flag(register_file, overflow);
    set_zero_flag(register_file, false);
    set_substraction_flag(register_file, false);
}

void process_instruction_and_r8(gb_register_file *register_file, target target)
{
    uint8_t* reg_ptr = get_reg_pointer(register_file, target);
    uint8_t* a_ptr = &register_file->a;
    *a_ptr = (*a_ptr & *reg_ptr);
    set_zero_flag(register_file, *a_ptr == 0);
    set_substraction_flag(register_file, false);
    set_half_carry_flag(register_file, true);
    set_carry_flag(register_file, false);
}

void process_instruction_and_hl(gb_register_file *register_file)
{
    uint8_t hl_byte = (uint8_t) get_hl_register_value(register_file);
    uint8_t* a_ptr = &register_file->a;
    *a_ptr = (*a_ptr & hl_byte);
    set_zero_flag(register_file, *a_ptr == 0);
    set_substraction_flag(register_file, false);
    set_half_carry_flag(register_file, true);
    set_carry_flag(register_file, false);
}

void process_instruction_and_n8(gb_register_file *register_file, uint8_t value)
{
    uint8_t* a_ptr = &register_file->a;
    *a_ptr = (*a_ptr & value);
    set_zero_flag(register_file, *a_ptr == 0);
    set_substraction_flag(register_file, false);
    set_half_carry_flag(register_file, true);
    set_carry_flag(register_file, false);
}

void process_instruction_bit_r8(gb_register_file *register_file, uint8_t value, target target)
{
    uint8_t* reg_ptr = get_reg_pointer(register_file, target);
    bool set = (*reg_ptr >> value) & 0b1;
    set_zero_flag(register_file, set);
    set_substraction_flag(register_file, false);
    set_half_carry_flag(register_file, true);
}

void process_instruction_bit_hl(gb_register_file *register_file, uint8_t value)
{
    uint8_t hl_val = get_hl_register_value(register_file);
    bool set = (hl_val >> value) & 0b1;
    set_zero_flag(register_file, set);
    set_substraction_flag(register_file, false);
    set_half_carry_flag(register_file, true);
}


void process_instruction_call_n16(gb_register_file *register_file, uint16_t value)
{
    stack_push(register_file, value);
    process_instruction_jp_n16(register_file, value);
}

void process_instruction_call_cc(gb_register_file *register_file, uint16_t value, bool cc)
{
    if(!cc) return;
    process_instruction_call_n16(register_file, value);
}

void process_instruction_ccf(gb_register_file *register_file)
{
    set_substraction_flag(register_file, false);
    set_half_carry_flag(register_file, false);
    set_carry_flag(register_file, get_carry_flag(register_file));
}

void process_instruction_cp_r8(gb_register_file *register_file, target target)
{
    uint8_t* reg_ptr = get_reg_pointer(register_file, target);
    process_sub_discarded(register_file, *reg_ptr);
}

void process_instruction_cp_hl(gb_register_file *register_file)
{
    uint8_t hl_val = (uint8_t) get_hl_register_value(register_file);
    process_sub_discarded(register_file, hl_val);
}

void process_instruction_cp_n8(gb_register_file *register_file, uint8_t value)
{
    process_sub_discarded(register_file, value);
}

void process_instruction_cpl(gb_register_file *register_file)
{
    uint8_t* reg_a = &register_file->a;
    *reg_a = ~(*reg_a);
    set_half_carry_flag(register_file, true);
    set_substraction_flag(register_file, true);
}

void process_instruction_jp_n16(gb_register_file *register_file, uint16_t value)
{
    register_file->pc = value;
}

void process_instruction_jp_cc(gb_register_file *register_file, uint16_t value, bool cc)
{
    if(!cc) return;
    process_instruction_jp_n16(register_file, value);
}

void process_instruction_jp_hl(gb_register_file *register_file)
{
    process_instruction_jp_n16(register_file, get_hl_register_value(register_file));
}

void process_instruction_ld_const(gb_register_file *register_file, target target, uint8_t value)
{
    uint8_t* reg_pointer = get_reg_pointer(register_file, target);
    if(reg_pointer)
    {
        *reg_pointer = value;
        return;
    }

    switch (target)
    {
        case HL:
            set_hl_register(register_file, (uint16_t) value);
            return;
        case BC:
            set_bc_register(register_file, (uint16_t) value);
            return;
        case DE:
            set_de_register(register_file, (uint16_t) value);
            return;
        case SP:
            *(&register_file->sp) = (uint16_t) value;
            return;
        default:
            return; //rip
    }
}

void process_instruction_ld_reg(gb_register_file *register_file, target target_reg, target source_reg)
{
    uint8_t* target_reg_ptr = get_reg_pointer(register_file, target_reg);
    uint8_t* source_reg_ptr = get_reg_pointer(register_file, target_reg);
    if(target_reg_ptr && source_reg_ptr)
    {
        *target_reg_ptr = *source_reg_ptr;
        return;
    }

    //hell nah we have to load into or from hl 💀
    if (!target_reg_ptr && !source_reg_ptr)
    {
        return; //basically a NOP instr
    }

    if(!target_reg_ptr) // we load into hl
    {
        set_hl_register(register_file, (uint16_t) *source_reg_ptr);
        return;
    }

    // we load from hl

    uint16_t value = get_hl_register_value(register_file);
    *target_reg_ptr = (uint8_t) (value >> 8); //LS byte first? shit this might be wrong
}

void process_sub_discarded(gb_register_file *register_file, uint8_t value)
{
    uint8_t tmp = 0;
    set_half_carry_flag(register_file, (register_file->a & 0xF) - (value & 0xF) > 0xF); //TODO check this
    __builtin_sub_overflow(register_file->a, value, &tmp);
    set_carry_flag(register_file, value > register_file->a);
    set_zero_flag(register_file, tmp == 0);
    set_substraction_flag(register_file, true);
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

    uint16_t tmp = 0;

    bool overflow = __builtin_add_overflow(hl_value, value, &tmp);
    set_hl_register(register_file, tmp);

    uint16_t new_hl_value = get_hl_register_value(register_file);

    set_carry_flag(register_file, overflow);
    set_zero_flag(register_file, new_hl_value == 0);
    set_substraction_flag(register_file, false);
}

#include "headers/stack.h"
#include <stdint.h>

void stack_push(gb_register_file* register_file, uint16_t value)
{
    uint16_t* stack_pointer = &register_file->sp;
    (*stack_pointer)--;
    write_to_gb_memory(register_file->gb_memory_ptr, *stack_pointer, (uint8_t) ((value & 0xFF00) >> 8));
    (*stack_pointer)--;
    write_to_gb_memory(register_file->gb_memory_ptr, *stack_pointer, (uint8_t) (value & 0x00FF));
}

uint16_t stack_pop(gb_register_file* register_file)
{
    uint16_t* stack_pointer = &register_file->sp;
    uint16_t lsb = read_from_gb_memory(register_file->gb_memory_ptr, *stack_pointer);
    (*stack_pointer)++;
    uint16_t msb = read_from_gb_memory(register_file->gb_memory_ptr, *stack_pointer);
    (*stack_pointer)++;
    return (msb << 8) | lsb;
}

#ifndef  _INSTRUCTIONS_H_
#define  _INSTRUCTIONS_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct gb_register_file {
    uint16_t pc; // program counter
    uint16_t sp; // stack pointer
    uint8_t  a;  // accumulator
    uint8_t  f;  // flags
    uint8_t  b;  // from B -> L general purpose
    uint8_t  c;
    uint8_t  d;
    uint8_t  e;
    uint8_t  h;
    uint8_t  l;
    uint8_t  ir; // instruction register
    uint8_t  ie; // interrupt enable
} gb_register_file;

gb_register_file* init_register_file();

/*
 * flags: ijkl 0000
 * i -> zero
 * j -> substraction
 * k -> half carry
 * l -> carry
 */

void set_zero_flag(gb_register_file* register_file, bool value);
bool get_zero_flag(gb_register_file* register_file);

void set_substraction_flag(gb_register_file* register_file, bool value);
bool get_substraction_flag(gb_register_file* register_file);

void set_half_carry_flag(gb_register_file* register_file, bool value);
bool get_half_carry_flag(gb_register_file* register_file);

void set_carry_flag(gb_register_file* register_file, bool value);
bool get_carry_flag(gb_register_file* register_file);


uint16_t get_bc_register_value(gb_register_file* register_file);
void     set_bc_register(gb_register_file* register_file, uint16_t value);

uint16_t get_de_register_value(gb_register_file* register_file);
void     set_de_register(gb_register_file* register_file, uint16_t value);

uint16_t get_hl_register_value(gb_register_file* register_file);
void     set_hl_register(gb_register_file* register_file, uint16_t value);

#endif

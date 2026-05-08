#ifndef  _REGISTER_FILE_H_
#define  _REGISTER_FILE_H_

#include <stdint.h>
#include <stdbool.h>

#define ZERO_FLAG_OFFSET 7
#define SUBSTRACTION_FLAG_OFFSET 6
#define HALF_CARRY_FLAG_OFFSET 5
#define CARRY_FLAG_OFFSET 4

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

typedef enum target {
    A, B, C, D, E, H, L, HL, BC, DE, SP
} target;

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

uint8_t* get_reg_pointer(gb_register_file* register_file, target target);

uint16_t get_bc_register_value(gb_register_file* register_file);
void     set_bc_register(gb_register_file* register_file, uint16_t value);

uint16_t get_de_register_value(gb_register_file* register_file);
void     set_de_register(gb_register_file* register_file, uint16_t value);

uint16_t get_hl_register_value(gb_register_file* register_file);
void     set_hl_register(gb_register_file* register_file, uint16_t value);

#endif

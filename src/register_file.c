#include "headers/register_file.h"

#include <stdint.h>
#include <stdlib.h>

gb_register_file* init_register_file()
{
    gb_register_file* register_file = malloc(sizeof(gb_register_file));
    if(!register_file)
    {
        return NULL;
    }

    return register_file;
}

void set_zero_flag(gb_register_file* register_file, bool value)
{
    uint8_t* f = &register_file->f;
    *f = (uint8_t) (*f & (value << ZERO_FLAG_OFFSET));
}
bool get_zero_flag(gb_register_file* register_file)
{
    uint8_t f = register_file->f;
    return (bool) (f >> ZERO_FLAG_OFFSET);
}

void set_substraction_flag(gb_register_file* register_file, bool value)
{
    uint8_t* f = &register_file->f;
    *f = (uint8_t) (*f & (value << SUBSTRACTION_FLAG_OFFSET));
}
bool get_substraction_flag(gb_register_file* register_file)
{
    uint8_t f = register_file->f;
    return (bool) ((f >> SUBSTRACTION_FLAG_OFFSET) & true);
}

void set_half_carry_flag(gb_register_file* register_file, bool value)
{
    uint8_t* f = &register_file->f;
    *f = (uint8_t) (*f & (value << HALF_CARRY_FLAG_OFFSET));
}
bool get_half_carry_flag(gb_register_file* register_file)
{
    uint8_t f = register_file->f;
    return (bool) ((f >> HALF_CARRY_FLAG_OFFSET) & true);
}

void set_carry_flag(gb_register_file* register_file, bool value)
{
    uint8_t* f = &register_file->f;
    *f = (uint8_t) (*f & (value << CARRY_FLAG_OFFSET));
}
bool get_carry_flag(gb_register_file* register_file)
{
    uint8_t f = register_file->f;
    return (bool) ((f >> CARRY_FLAG_OFFSET) & true);
}

uint16_t get_bc_register_value(gb_register_file* register_file)
{
    uint16_t b = (uint16_t) register_file->b;
    uint16_t c = (uint16_t) register_file->c;
    return (uint16_t) ((b << 8) | c);
}
void set_bc_register(gb_register_file* register_file, uint16_t value)
{
    uint8_t* b = &register_file->b;
    *b = (uint8_t) ((value & 0xFF00) >> 8); // shift to the right because little endian

    uint8_t* c = &register_file->c;
    *c = (uint8_t) ((value & 0xFF) << 8);
}


uint16_t get_de_register_value(gb_register_file* register_file)
{
    uint16_t d = (uint16_t) register_file->d;
    uint16_t e = (uint16_t) register_file->e;
    return (uint16_t) ((d << 8) | e);
}
void set_de_register(gb_register_file* register_file, uint16_t value)
{
    uint8_t* d = &register_file->d;
    *d = (uint8_t) ((value & 0xFF00) >> 8);

    uint8_t* e = &register_file->e;
    *e = (uint8_t) ((value & 0xFF) << 8);
}


uint16_t get_hl_register_value(gb_register_file* register_file)
{
    uint16_t h = (uint16_t) register_file->h;
    uint16_t l = (uint16_t) register_file->l;
    return (uint16_t) ((h << 8) | l);
}
void set_hl_register(gb_register_file* register_file, uint16_t value)
{
    uint8_t* h = &register_file->h;
    *h = (uint8_t) ((value & 0xFF00) >> 8);

    uint8_t* l = &register_file->l;
    *l = (uint8_t) ((value & 0xFF) << 8);
}

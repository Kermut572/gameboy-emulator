#ifndef _STACK_H_
#define _STACK_H_

#include "register_file.h"
#include <stdint.h>

void stack_push(gb_register_file* register_file, uint16_t value);
uint16_t stack_pop(gb_register_file* register_file);

#endif

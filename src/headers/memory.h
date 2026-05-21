#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdint.h>

typedef struct gb_memory {
    uint8_t* bus;
} gb_memory;

gb_memory* init_gb_memory();
void free_gb_memory(gb_memory* gb_memory_ptr);

uint8_t read_from_gb_memory(gb_memory* gb_memory_ptr, uint16_t addr);
void write_to_gb_memory(gb_memory* gb_memory_ptr, uint16_t addr, uint8_t value);

#endif

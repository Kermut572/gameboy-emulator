#include "headers/memory.h"
#include <stdint.h>
#include <stdlib.h>

gb_memory* init_gb_memory()
{
    gb_memory* gb_memory_ptr = malloc(sizeof(gb_memory));
    if(!gb_memory_ptr)
    {
        return NULL;
    }

    gb_memory_ptr->bus = malloc(0xFFFF);
    if(!gb_memory_ptr->bus)
    {
        free(gb_memory_ptr);
        return NULL;
    }

    return gb_memory_ptr;
}

void free_gb_memory(gb_memory* gb_memory_ptr)
{
    free(gb_memory_ptr->bus);
    free(gb_memory_ptr);
}

uint8_t read_from_gb_memory(gb_memory* gb_memory_ptr, uint16_t addr)
{
    return gb_memory_ptr->bus[addr];
}

void write_to_gb_memory(gb_memory* gb_memory_ptr, uint16_t addr, uint8_t value)
{
    gb_memory_ptr->bus[addr] = value;
}

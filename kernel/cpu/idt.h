#pragma once
#include <utils.h>

pstruct
{
    uint16_t size;
    uint64_t offset;
} idtr_t;

pstruct
{
    uint16_t offset;
    uint16_t segmentselector;
    uint8_t ist;
    uint8_t attributes;
    uint16_t offset2;
    uint32_t offset3;
    uint32_t reserved;
} idt_gate_descriptor_t;

void idtSetGate(uint8_t vector, void *ptr);
void idtInit();
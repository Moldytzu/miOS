#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdnoreturn.h>
#include <limine.h>

// this file implements some of the basic libc libraries and some utility macros & functions

#define iasm asm volatile
#define ifunc __attribute__((always_inline)) inline static
#define pstruct typedef struct __attribute__((packed))
#define zero(ptr, type) memset(ptr, 0, sizeof(type))

int strlen(const char *str);

void memset(void *dest, uint8_t data, size_t count);
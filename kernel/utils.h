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
#define zero(ptr, type) memset((void *)(ptr), 0, sizeof(type))
#define align(val, alg) (max(val,alg) + (alg - (max(val,alg) % alg)))
#define alignD(val, alg) (align(val, alg) - alg)

int strlen(const char *str);
void memcpy(void *dest, void *src, size_t count);
void memset(void *dest, uint8_t data, size_t count);
int memcmp(void *a, void *b, size_t count);
const char *to_string(uint64_t val);
const char *to_hstring(uint64_t val);
void strrev(char *str);

ifunc int min(int a, int b)
{
    if (a > b)
        return b;

    return a;
}

ifunc int max(int a, int b)
{
    if (a > b)
        return a;

    return b;
}
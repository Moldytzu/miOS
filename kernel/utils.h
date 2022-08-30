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

int strlen(const char *str);

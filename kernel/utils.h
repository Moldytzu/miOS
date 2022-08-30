#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdnoreturn.h>
#include <limine.h>

// this file implements some of the basic libc libraries

int strlen(char *str);

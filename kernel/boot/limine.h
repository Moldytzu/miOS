#include <utils.h>

// this file wraps the limine response handling

struct limine_terminal *limineGetTerminal();

void limineInit();
void limineWrite(const char *str);
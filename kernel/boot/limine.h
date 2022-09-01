#include <utils.h>

// this file wraps the limine response handling

struct limine_terminal *limineGetTerminal();
struct limine_memmap_response *limineGetMemmap();
uint64_t limineGetHHDM();

void limineInit();
void limineWrite(const char *str);
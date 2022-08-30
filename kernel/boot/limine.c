#include <boot/limine.h>

// requests
static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0};

// responses
struct limine_terminal *terminal;

void limineInit()
{
    terminal = terminal_request.response->terminals[0]; // set the default terminal to the first one

    if (terminal_request.response == NULL || terminal_request.response->terminal_count == 0) // hang if there isn't any terminal available
        while(1);
}

void limineWrite(const char *str)
{
    terminal_request.response->write(terminal, str, strlen(str)); // write the string on the default terminal
}
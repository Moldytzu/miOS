#include <sys/syscall.h>
#include <io/serial.h>

void syscallHandler(void *rsp)
{
    serialWrites("Syscall!");
}
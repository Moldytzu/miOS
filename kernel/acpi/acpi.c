#include <acpi/acpi.h>
#include <io/serial.h>

static volatile struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0};

acpi_rsdp_t *rsdp;

void acpiInit()
{
    rsdp = (acpi_rsdp_t *)rsdp_request.response->address;

    serialWrites("RSDP signature: ");

    for(int i = 0; i < 8; i++)
        serialWrite(rsdp->signature[i]);

    serialWrite('\n');

    if (memcmp(rsdp->signature, "RSD PTR ", 8) != 0)
        serialWrites("Invalid signature!\n");
}
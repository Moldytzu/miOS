#include <acpi/acpi.h>
#include <io/serial.h>

static volatile struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0};

acpi_rsdp_t *rsdp = NULL;
acpi_xsdt_t *xsdt = NULL;
acpi_rsdt_t *rsdt = NULL;

void *acpiScan(char *signature)
{
    if (xsdt)
    {
        uint64_t entries = (xsdt->header.length - sizeof(xsdt->header)) / sizeof(uint64_t);

        for (size_t i = 0; i < entries; i++)
        {
            acpi_header_t *entry = (acpi_header_t *)xsdt->entries[i];
            if (memcmp(entry->signature, signature, 4) == 0)
                return entry;
        }

        return NULL;
    }

    uint32_t entries = (rsdt->header.length - sizeof(rsdt->header)) / sizeof(uint32_t);

    for (size_t i = 0; i < entries; i++)
    {
        acpi_header_t *entry = (acpi_header_t *)rsdt->entries[i];
        
        if (memcmp(signature, entry->signature, 4) == 0)
            return entry;
    }

    return NULL;
}

void acpiInit()
{
    rsdp = (acpi_rsdp_t *)rsdp_request.response->address;

    serialWrites("RSDP signature: ");

    for (int i = 0; i < 8; i++)
        serialWrite(rsdp->signature[i]);

    serialWrites("; Revision: ");
    serialWrites(to_string(rsdp->revision));
    serialWrite('\n');

    if (memcmp(rsdp->signature, "RSD PTR ", 8) != 0)
        serialWrites("Invalid signature!\n");

    rsdt = (acpi_rsdt_t *)(uint64_t)rsdp->rsdt;

    if (rsdp->revision > 0) // xsdt is available in revisions > 0 of the rsdp
        xsdt = (acpi_xsdt_t *)rsdp->xsdt;

    acpi_header_t *madt = acpiScan("APIC");
    for (int i = 0; i < 4; i++)
        serialWrite(madt->signature[i]);
}
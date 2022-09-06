#pragma once
#include <utils.h>

pstruct
{
    uint8_t signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    uint8_t oemid[6];
    uint8_t oemtableid[8];
    uint32_t oemrevision;
    uint32_t creatorid;
    uint32_t creatorrevision;
} acpi_header_t;

pstruct
{
    uint8_t signature[8];
    uint8_t checksum;
    uint8_t oemid[6];
    uint8_t revision;
    uint32_t rsdt;
    uint32_t length;
    uint64_t xsdt;
    uint8_t extendedChecksum;
    uint8_t reserved[3];
} acpi_rsdp_t;

pstruct
{
    acpi_header_t header;
    uint32_t entries[]; 
} acpi_rsdt_t;

pstruct
{
    acpi_header_t header;
    uint64_t entries[]; 
} acpi_xsdt_t;

void *acpiScan(char *signature);
void acpiInit();
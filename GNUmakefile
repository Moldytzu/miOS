BINDIR = bin
DVD = $(BINDIR)/dvd.iso

.PHONY: all run run-uefi kernel limine clean distclean

all: $(DVD)

run: $(DVD)
	qemu-system-x86_64 -M q35 -m 2G -cdrom $(DVD) -boot d

run-uefi: ovmf-x64 $(DVD)
	qemu-system-x86_64 -M q35 -m 2G -bios ovmf-x64/OVMF.fd -cdrom $(DVD) -boot d

ovmf-x64:
	mkdir -p ovmf-x64
	cd ovmf-x64 && curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip && 7z x OVMF-X64.zip

limine:
	-git clone https://github.com/limine-bootloader/limine.git --branch=v3.0-branch-binary --depth=1 --
	make -C limine

kernel:
	$(MAKE) -C kernel

$(DVD): limine kernel
	rm -rf iso_root
	mkdir -p iso_root $(BINDIR)
	cp $(BINDIR)/kernel.elf \
		limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-cd-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o $(DVD)
	limine/limine-deploy $(DVD)
	rm -rf iso_root

clean:
	rm -rf iso_root $(DVD)
	$(MAKE) -C kernel clean

distclean: clean
	rm -rf limine ovmf-x64
	$(MAKE) -C kernel distclean

OPTIMIZATION_LEVEL = fast
HARDWARE           = RPI

CPU       = arm1176jzf-s
TOOLCHAIN = arm-none-eabi

CFLAGS  = -Wall -Werror -O$(OPTIMIZATION_LEVEL) -D$(HARDWARE) -mfpu=vfp -mfloat-abi=hard -mcpu=$(CPU) -nostdlib -nostartfiles -ffreestanding
ASFLAGS = -mcpu=$(CPU)

.PHONY: all clean run

all: kernel.img

boot.o: boot.S
	$(TOOLCHAIN)-as $(ASFLAGS) -g $< -o $@

kernel.o: kernel.c librpi/librpi.h
	$(TOOLCHAIN)-gcc $(CFLAGS) -c $< -o $@

librpi.o: librpi/librpi.c librpi/librpi.h
	$(TOOLCHAIN)-gcc $(CFLAGS) -c $< -o $@

kernel.elf: linker.ld kernel.o librpi.o boot.o
	$(TOOLCHAIN)-ld -T $^ -o $@

kernel.img: kernel.elf
	$(TOOLCHAIN)-objcopy -O binary $< $@

run: kernel.img
	qemu-system-arm -M versatilepb -m 128M -no-reboot -nographic -kernel $<

clean:
	rm -f ./*.o
	rm -f ./*.elf
	rm -f ./*.img

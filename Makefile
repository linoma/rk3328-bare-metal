#
# Copyright (C) 2018 bzt (bztsrc@github)
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use, copy,
# modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
#

SRCS = $(wildcard *.c)
#SRCS += $(wildcard *.S)
OBJS = $(SRCS:.c=.o)
OBJS += cache.o

CFLAGS = -Wno-int-to-pointer-cast -O2 -ffreestanding -fno-stack-protector -nostdinc -nostdlib -nostartfiles -march=armv8-a -fno-pie
TARGET_USER	= kernel.elf
TARGET_KERN = kernel

all: clean kernel.bin

%.o: %.S
	@echo Assemblling  $< ...
	@aarch64-linux-gnu-gcc $(CFLAGS) -c $< -o $@

%.o: %.c
	@echo Compiling  $< ...
	@aarch64-linux-gnu-gcc $(CFLAGS) -c $< -o $@

kernel.bin: start.o $(OBJS)
	@echo Building kernel.bin ...
	@aarch64-linux-gnu-ld -nostdlib -nostartfiles start.o $(OBJS) -T link.ld -o $(TARGET_USER)
	@aarch64-linux-gnu-objcopy -O binary $(TARGET_USER) kernel.bin

clean:
	@rm *.elf >/dev/null 2>/dev/null || true
	@rm kernel.bin >/dev/null 2>/dev/null || true
	@rm *.o >/dev/null 2>/dev/null || true
	@rm *.s >/dev/null 2>/dev/null || true
	@rm *.i >/dev/null 2>/dev/null || true

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio

upload:
	/home/lino/u-boot/tools/mkimage -n rk3328 -T rksd -d kernel.bin boot.img
	sudo dd if=boot.img of=/dev/sdb seek=64 oflag=sync

install:
	cp kernel.bin /media/lino/BOOT
	umount /dev/sdb1
	umount /dev/sdb2
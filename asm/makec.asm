nasm boot.asm -f bin -o bootloader.bin
nasm extended.asm -f elf64 -o extended.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c kernel.cpp -o kernel.o
x86_64-elf-ld -o kernel.tmp -Ttext 0x7e00 extended.o
objcopy -O binary kernel.tmp kernel.bin
copy /b boot.bin+kernel.bin bootloader.bin
qemu-system-x86_64 bootloader.bin
cd asm/

wsl nasm boot.asm -f bin -o ../bin/boot.bin
wsl nasm extended.asm -f elf64 -o ../out/extended.o
wsl nasm zeroes.asm -f bin -o ../bin/zeroes.bin

cd ../

wsl /usr/local/x86_64elfgcc/bin/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -Wno-write-strings -Wno-int-to-pointer-cast -c "./cpp/kernel.cpp" -o "./out/kernel.o"
wsl /usr/local/x86_64elfgcc/bin/x86_64-elf-ld -N -T "link.ld"
wsl cat "./bin/boot.bin" "./bin/kernel.bin" "./bin/zeroes.bin" > "OS.bin"
qemu-system-x86_64 OS.bin
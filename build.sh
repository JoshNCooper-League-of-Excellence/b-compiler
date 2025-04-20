nasm -felf64 $1.asm -o $1.o

clang $1.o -o $1 -lc -nostartfiles -no-pie -g

./expected

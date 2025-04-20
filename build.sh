program_name="expected"

if [ -n "$1" ]; then
  program_name=$1
  shift
fi

nasm "$program_name.asm" -felf64 -o "$program_name.o" && 
  clang "$program_name.o" -o "$program_name" -nostartfiles -no-pie "$@" && ./"$program_name"

rm "$program_name.o"
echo -e "program returned\033[1;3;34m" $? "\033[0m"
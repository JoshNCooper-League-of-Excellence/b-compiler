

puts(string) {
  extern strlen; auto i;
  i = 0;

  while (i < strlen(string)) {
    puts(string[i]);
    i = i + 1;
  }
}

main() {
  extrn putchar; extrn exit;

  auto helloWorld[13] = "Hello World!\n";


  exit(0);
}
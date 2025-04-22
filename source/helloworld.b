

hello_world() {
  putchar('H');
  putchar('e');
  putchar('l');
  putchar('l');
  putchar('o');
  putchar(',');
  putchar(' ');
  putchar('W');
  putchar('o');
  putchar('r');
  putchar('l');
  putchar('d');
  putchar('!');
  putchar('\n');
}

main() {
  extrn putchar;
  extrn exit;
  hello_world();
  exit(0);
}
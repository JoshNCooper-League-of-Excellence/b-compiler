
func(a, b) {
  auto x;
  x = a + b;
}

main() {
  extrn exit;
  func(1 + 2, 2 + 3 * 200);
  exit(0);
}


func(a, b) {
  auto x;
  x = a + b;
}

main() {
  extrn exit;
  auto v;
  v = 1 + 2, 2 + 3 * 200;
  func(v, 10);
  exit(0);
}

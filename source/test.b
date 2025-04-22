
func(a, b) {
  auto x;
  x = a + b;
}

_start() {
  extrn exit;
  func(1, 2);
  exit(0);
}

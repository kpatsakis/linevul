MATCHER_P2(EqualsMouseEvent, x, y, "") {
  return arg.x() == x && arg.y() == y;
}

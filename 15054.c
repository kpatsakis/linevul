MATCHER_P2(EqualsKeyEvent, keycode, pressed, "") {
  return arg.keycode() == keycode && arg.pressed() == pressed;
}

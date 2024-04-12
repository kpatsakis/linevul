int tab_h_offset() {
  static int value = -1;
  if (value == -1) {
    switch (ui::GetDisplayLayout()) {
      case ui::LAYOUT_DESKTOP:
        value = -26;
        break;
      case ui::LAYOUT_TOUCH:
        value = -34;
        break;
      default:
        NOTREACHED();
    }
  }
  return value;
}

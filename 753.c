gfx::Image* TabStripGtk::GetDropArrowImage(bool is_down) {
  return &ui::ResourceBundle::GetSharedInstance().GetNativeImageNamed(
      is_down ? IDR_TAB_DROP_DOWN : IDR_TAB_DROP_UP);
}

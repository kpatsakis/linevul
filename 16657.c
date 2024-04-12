gfx::ImageSkia* TabStrip::GetDropArrowImage(bool is_down) {
  return ui::ResourceBundle::GetSharedInstance().GetImageSkiaNamed(
      is_down ? IDR_TAB_DROP_DOWN : IDR_TAB_DROP_UP);
}

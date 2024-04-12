void Textfield::SetStyle(gfx::TextStyle style, bool value) {
  GetRenderText()->SetStyle(style, value);
  SchedulePaint();
}

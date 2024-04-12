void Textfield::ApplyColor(SkColor value, const gfx::Range& range) {
  GetRenderText()->ApplyColor(value, range);
  SchedulePaint();
}

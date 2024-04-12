gfx::Size Textfield::CalculatePreferredSize() const {
  const gfx::Insets& insets = GetInsets();
  return gfx::Size(
      GetFontList().GetExpectedTextWidth(default_width_in_chars_) +
          insets.width(),
      LayoutProvider::GetControlHeightForFont(style::CONTEXT_TEXTFIELD,
                                              GetTextStyle(), GetFontList()));
}

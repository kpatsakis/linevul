SkColor Textfield::GetSelectionTextColor() const {
  return use_default_selection_text_color_
             ? GetNativeTheme()->GetSystemColor(
                   ui::NativeTheme::kColorId_TextfieldSelectionColor)
             : selection_text_color_;
}

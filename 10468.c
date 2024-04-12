void FolderHeaderView::Layout() {
  gfx::Rect rect(GetContentsBounds());
  if (rect.IsEmpty())
    return;

  gfx::Rect back_bounds(rect);
  back_bounds.set_width(kIconDimension + 2 * kPadding);
  back_button_->SetBoundsRect(back_bounds);

  gfx::Rect text_bounds(rect);
  int text_char_num = folder_item_->name().size()
                          ? folder_item_->name().size()
                          : folder_name_placeholder_text_.size();
  int text_width = folder_name_view_->GetFontList().GetExpectedTextWidth(
      text_char_num + kFolderNameLeftRightPaddingChars);
  text_width = std::min(text_width, kMaxFolderNameWidth);
  text_bounds.set_x(back_bounds.x() + (rect.width() - text_width) / 2);
  text_bounds.set_width(text_width);
  text_bounds.ClampToCenteredSize(gfx::Size(text_bounds.width(),
      folder_name_view_->GetPreferredSize().height()));
  folder_name_view_->SetBoundsRect(text_bounds);
}

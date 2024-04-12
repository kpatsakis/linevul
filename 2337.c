void BrowserView::NativeThemeUpdated(const ui::NativeTheme* theme) {

  if (!initialized_)
    return;
  if (!handling_theme_changed_)
    UserChangedTheme();
  MaybeShowInvertBubbleView(this);
}

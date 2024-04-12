bool Browser::IsPopup(const TabContents* source) const {
  return !!(type() & TYPE_POPUP);
}

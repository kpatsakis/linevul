ui::Clipboard* ClipboardMessageFilter::GetClipboard() {
  static ui::Clipboard* clipboard = new ui::Clipboard;

  return clipboard;
}

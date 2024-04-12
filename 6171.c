ui::Clipboard* ClipboardMessageFilter::GetClipboard() {
  static ui::Clipboard* clipboard = ui::Clipboard::GetForCurrentThread();
  return clipboard;
}

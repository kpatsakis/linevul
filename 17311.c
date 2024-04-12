Clipboard* ResourceMessageFilter::GetClipboard() {
  static Clipboard* clipboard = new Clipboard;

  return clipboard;
}

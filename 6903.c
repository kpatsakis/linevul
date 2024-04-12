static bool ExecuteCut(LocalFrame& frame,
                       Event*,
                       EditorCommandSource source,
                       const String&) {
  if (!CanWriteClipboard(frame, source))
    return false;
  frame.GetEditor().Cut(source);
  return true;
}

bool SystemClipboard::IsValidBufferType(mojom::ClipboardBuffer buffer) {
  switch (buffer) {
    case mojom::ClipboardBuffer::kStandard:
      return true;
    case mojom::ClipboardBuffer::kSelection:
#if defined(USE_X11)
      return true;
#else
      return false;
#endif
  }
  return true;
}

static bool NeedsHistoryItemRestore(FrameLoadType type) {
  return type == kFrameLoadTypeBackForward || IsReloadLoadType(type);
}

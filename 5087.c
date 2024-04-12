bool PrintRenderFrameHelper::PrintPreviewContext::HasSelection() {
  return IsModifiable() && source_frame()->HasSelection();
}

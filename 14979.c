void WebContentsImpl::ReplaceMisspelling(const base::string16& word) {
  RenderFrameHostImpl* focused_frame = GetFocusedFrame();
  if (!focused_frame)
    return;

  focused_frame->GetFrameInputHandler()->ReplaceMisspelling(word);
}

void WebContentsImpl::OnShowValidationMessage(
    RenderViewHostImpl* source,
    const gfx::Rect& anchor_in_root_view,
    const base::string16& main_text,
    const base::string16& sub_text) {
  if (delegate_)
    delegate_->ShowValidationMessage(
        this, anchor_in_root_view, main_text, sub_text);
}

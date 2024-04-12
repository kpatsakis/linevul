void RenderFrameImpl::OnSelectPopupMenuItem(int selected_index) {
  if (external_popup_menu_ == NULL)
    return;

  blink::WebScopedUserGesture gesture(frame_);
  std::unique_ptr<ExternalPopupMenu> popup;
  popup.swap(external_popup_menu_);
  popup->DidSelectItem(selected_index);
}

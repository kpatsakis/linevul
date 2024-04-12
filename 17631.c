void RenderViewImpl::OnSelectPopupMenuItems(
    bool canceled,
    const std::vector<int>& selected_indices) {
  if (!external_popup_menu_.get())
    return;

  external_popup_menu_->DidSelectItems(canceled, selected_indices);
  external_popup_menu_.reset();
}

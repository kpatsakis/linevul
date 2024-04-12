HWND TreeView::CreateNativeControl(HWND parent_container) {
  int style = WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_SHOWSELALWAYS;
  if (!drag_enabled_)
    style |= TVS_DISABLEDRAGDROP;
  if (editable_)
    style |= TVS_EDITLABELS;
  if (lines_at_root_)
    style |= TVS_LINESATROOT;
  tree_view_ = ::CreateWindowEx(WS_EX_CLIENTEDGE | GetAdditionalExStyle(),
                                WC_TREEVIEW,
                                L"",
                                style,
                                0, 0, width(), height(),
                                parent_container, NULL, NULL, NULL);
  ui::CheckWindowCreated(tree_view_);
  SetWindowLongPtr(tree_view_, GWLP_USERDATA,
                   reinterpret_cast<LONG_PTR>(&wrapper_));
  original_handler_ = ui::SetWindowProc(tree_view_, &TreeWndProc);
  l10n_util::AdjustUIFontForWindow(tree_view_);

  if (model_) {
    CreateRootItems();
    AddObserverToModel();
    image_list_ = CreateImageList();
    TreeView_SetImageList(tree_view_, image_list_, TVSIL_NORMAL);
  }

  ::ImmAssociateContextEx(tree_view_, NULL, 0);
  return tree_view_;
}

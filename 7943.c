ShelfLayoutManager::ShelfLayoutManager(views::Widget* status)
    : root_window_(Shell::GetPrimaryRootWindow()),
      in_layout_(false),
      auto_hide_behavior_(SHELF_AUTO_HIDE_BEHAVIOR_DEFAULT),
      alignment_(SHELF_ALIGNMENT_BOTTOM),
      launcher_(NULL),
      status_(status),
      workspace_manager_(NULL),
      window_overlaps_shelf_(false) {
  Shell::GetInstance()->AddShellObserver(this);
  aura::client::GetActivationClient(root_window_)->AddObserver(this);
}

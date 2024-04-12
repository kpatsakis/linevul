FindBarController* Browser::GetFindBarController() {
  if (!find_bar_controller_.get()) {
    FindBar* find_bar = BrowserWindow::CreateFindBar(this);
    find_bar_controller_.reset(new FindBarController(find_bar));
    find_bar->SetFindBarController(find_bar_controller_.get());
    find_bar_controller_->ChangeTabContents(GetSelectedTabContents());
    find_bar_controller_->find_bar()->MoveWindowIfNecessary(gfx::Rect(), true);
  }
  return find_bar_controller_.get();
}

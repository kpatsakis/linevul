void ShelfLayoutManager::UpdateWorkspaceMask(
    wm::WorkspaceWindowState window_state) {
  auto* root_window_controller =
      RootWindowController::ForWindow(shelf_widget_->GetNativeWindow());
  auto* container = root_window_controller->GetContainer(
      kShellWindowId_NonLockScreenContainersContainer);
  switch (window_state) {
    case wm::WORKSPACE_WINDOW_STATE_MAXIMIZED:
    case wm::WORKSPACE_WINDOW_STATE_FULL_SCREEN:
      container->layer()->SetMasksToBounds(false);
      break;
    case wm::WORKSPACE_WINDOW_STATE_DEFAULT:
      container->layer()->SetMasksToBounds(true);
      break;
  }
}

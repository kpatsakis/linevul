bool AllRootWindowsHaveModalBackgroundsForContainer(int container_id) {
  aura::Window::Windows containers =
      wm::GetContainersFromAllRootWindows(container_id);
  bool has_modal_screen = !containers.empty();
  for (aura::Window* container : containers) {
    has_modal_screen &= static_cast<SystemModalContainerLayoutManager*>(
                            container->layout_manager())
                            ->has_window_dimmer();
  }
  return has_modal_screen;
}

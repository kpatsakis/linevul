void MoveAllTransientChildrenToNewRoot(const gfx::Display& display,
                                       aura::Window* window) {
  aura::Window* dst_root = Shell::GetInstance()
                               ->window_tree_host_manager()
                               ->GetRootWindowForDisplayId(display.id());
  aura::Window::Windows transient_children =
      ::wm::GetTransientChildren(window);
  for (aura::Window::Windows::iterator iter = transient_children.begin();
       iter != transient_children.end(); ++iter) {
    aura::Window* transient_child = *iter;
    int container_id = transient_child->parent()->id();
    DCHECK_GE(container_id, 0);
    aura::Window* container = Shell::GetContainer(dst_root, container_id);
    gfx::Rect parent_bounds_in_screen = transient_child->GetBoundsInScreen();
    container->AddChild(transient_child);
    transient_child->SetBoundsInScreen(parent_bounds_in_screen, display);

    MoveAllTransientChildrenToNewRoot(display, transient_child);
  }
  aura::Window::Windows children = window->children();
  for (aura::Window::Windows::iterator iter = children.begin();
       iter != children.end(); ++iter)
    MoveAllTransientChildrenToNewRoot(display, *iter);
}

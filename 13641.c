  aura::Window* GetPanelContainer(aura::Window* panel) {
    return Shell::GetContainer(panel->GetRootWindow(),
                               kShellWindowId_PanelContainer);
  }

  void ResizeDesktop(int width_delta) {
    gfx::Size size =
        display::Screen::GetScreen()
            ->GetDisplayNearestWindow(Shell::GetPrimaryRootWindow())
            .size();
    size.Enlarge(0, width_delta);
    UpdateDisplay(size.ToString());
  }

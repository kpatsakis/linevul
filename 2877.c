  bool IsDoneAnimating() const {
    gfx::Rect current_bounds = GetShelfWidget()->GetWindowBoundsInScreen();
    return current_bounds.origin() == target_bounds_.origin();
  }

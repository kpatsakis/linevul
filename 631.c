ShellSurface::ShellSurface(Surface* surface,
                           ShellSurface* parent,
                           const gfx::Rect& initial_bounds,
                           bool activatable,
                           int container)
    : widget_(nullptr),
      surface_(surface),
      parent_(parent ? parent->GetWidget()->GetNativeWindow() : nullptr),
      initial_bounds_(initial_bounds),
      activatable_(activatable),
      container_(container),
      pending_show_widget_(false),
      scale_(1.0),
      pending_scale_(1.0),
      scoped_configure_(nullptr),
      ignore_window_bounds_changes_(false),
      resize_component_(HTCAPTION),
      pending_resize_component_(HTCAPTION) {
  ash::Shell::GetInstance()->activation_client()->AddObserver(this);
  surface_->SetSurfaceDelegate(this);
  surface_->AddSurfaceObserver(this);
  surface_->window()->Show();
  set_owned_by_client();
  if (parent_)
    parent_->AddObserver(this);
}

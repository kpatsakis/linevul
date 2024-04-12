  void OnDraw(bool resourceless_software_draw) {
    gfx::Transform identity;
    gfx::Rect empty_rect;
    client_->OnDraw(identity, empty_rect, resourceless_software_draw);
  }

gfx::Size GuestViewBase::GetDefaultSize() const {
  if (is_full_page_plugin()) {
    return owner_web_contents()
        ->GetRenderWidgetHostView()
        ->GetVisibleViewportSize();
  } else {
    return gfx::Size(guestview::kDefaultWidth, guestview::kDefaultHeight);
  }
}

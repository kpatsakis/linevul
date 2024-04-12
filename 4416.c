void WindowTreeHostManager::SetOverscanInsets(
    int64_t display_id,
    const gfx::Insets& insets_in_dip) {
  GetDisplayManager()->SetOverscanInsets(display_id, insets_in_dip);
}

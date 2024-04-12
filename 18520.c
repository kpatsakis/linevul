void Browser::SaveWindowPlacement(const gfx::Rect& bounds,
                                  ui::WindowShowState show_state) {
  SessionService* session_service =
      SessionServiceFactory::GetForProfileIfExisting(profile());
  if (session_service)
    session_service->SetWindowBounds(session_id_, bounds, show_state);
}

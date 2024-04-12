Browser::CreateParams Browser::CreateParams::CreateForApp(
    const std::string& app_name,
    bool trusted_source,
    const gfx::Rect& window_bounds,
    Profile* profile) {
  DCHECK(!app_name.empty());

  CreateParams params(TYPE_POPUP, profile);
  params.app_name = app_name;
  params.trusted_source = trusted_source;
  params.initial_bounds = window_bounds;

  return params;
}

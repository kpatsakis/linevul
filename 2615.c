void PaintBackgroundAttachedMode(gfx::Canvas* canvas,
                                 const ui::ThemeProvider* theme_provider,
                                 const gfx::Rect& bounds,
                                 const gfx::Point& background_origin) {
  canvas->DrawColor(theme_provider->GetColor(ThemeProperties::COLOR_TOOLBAR));

  if (theme_provider->HasCustomImage(IDR_THEME_TOOLBAR)) {
    canvas->TileImageInt(*theme_provider->GetImageSkiaNamed(IDR_THEME_TOOLBAR),
                         background_origin.x(),
                         background_origin.y(),
                         bounds.x(),
                         bounds.y(),
                         bounds.width(),
                         bounds.height());
  }
}

AutocompletePopupViewGtk::AutocompletePopupViewGtk(
    AutocompleteEditView* edit_view,
    AutocompleteEditModel* edit_model,
    Profile* profile,
    GtkWidget* location_bar)
    : model_(new AutocompletePopupModel(this, edit_model, profile)),
      edit_view_(edit_view),
      location_bar_(location_bar),
      window_(gtk_window_new(GTK_WINDOW_POPUP)),
      layout_(NULL),
      theme_provider_(GtkThemeProvider::GetFrom(profile)),
      ignore_mouse_drag_(false),
      opened_(false) {
  GTK_WIDGET_UNSET_FLAGS(window_, GTK_CAN_FOCUS);
  gtk_window_set_resizable(GTK_WINDOW(window_), FALSE);
  gtk_widget_set_app_paintable(window_, TRUE);
  gtk_widget_set_double_buffered(window_, TRUE);

  layout_ = gtk_widget_create_pango_layout(window_, NULL);
  pango_layout_set_auto_dir(layout_, FALSE);
  pango_layout_set_ellipsize(layout_, PANGO_ELLIPSIZE_END);
  gfx::Font font = gfx::Font::CreateFont(
      gfx::Font().FontName(), browser_defaults::kAutocompletePopupFontSize);
  PangoFontDescription* pfd = gfx::Font::PangoFontFromGfxFont(font);
  pango_layout_set_font_description(layout_, pfd);
  pango_font_description_free(pfd);

  gtk_widget_add_events(window_, GDK_BUTTON_MOTION_MASK |
                                 GDK_POINTER_MOTION_MASK |
                                 GDK_BUTTON_PRESS_MASK |
                                 GDK_BUTTON_RELEASE_MASK);
  g_signal_connect(window_, "motion-notify-event",
                   G_CALLBACK(&HandleMotionThunk), this);
  g_signal_connect(window_, "button-press-event",
                   G_CALLBACK(&HandleButtonPressThunk), this);
  g_signal_connect(window_, "button-release-event",
                   G_CALLBACK(&HandleButtonReleaseThunk), this);
  g_signal_connect(window_, "expose-event",
                   G_CALLBACK(&HandleExposeThunk), this);

  registrar_.Add(this,
                 NotificationType::BROWSER_THEME_CHANGED,
                 NotificationService::AllSources());
  theme_provider_->InitThemesFor(this);

}

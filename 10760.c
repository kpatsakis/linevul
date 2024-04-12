void TabContentsContainerGtk::SetTab(TabContents* tab) {
  if (tab_ == tab)
    return;

  if (tab_)
    HideTab(tab_);

  tab_ = tab;

  if (tab_) {
    if (tab_ == preview_)
      preview_ = NULL;
    else
      PackTab(tab_);

    GtkWidget* widget = tab_->web_contents()->GetContentNativeView();
    if (widget) {
      GdkWindow* content_gdk_window = gtk_widget_get_window(widget);
      if (content_gdk_window)
        gdk_window_lower(content_gdk_window);
    }
  }
}

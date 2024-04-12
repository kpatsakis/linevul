OxideQWebPreferences* OxideQQuickWebView::preferences() {
  Q_D(OxideQQuickWebView);

  if (!d->proxy_) {
    if (!d->construct_props_->preferences) {
      d->construct_props_->preferences = new OxideQWebPreferences(this);
    }
    return d->construct_props_->preferences;
  }

  return d->proxy_->preferences();
}

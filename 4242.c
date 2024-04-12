void OxideQQuickWebView::setUrl(const QUrl& url) {
  Q_D(OxideQQuickWebView);

  QUrl old_url = this->url();

  if (!d->proxy_) {
    d->construct_props_->load_html = false;
    d->construct_props_->url = url;
    d->construct_props_->html.clear();
  } else {
    d->proxy_->setUrl(url);
  }

  if (this->url() != old_url) {
    emit urlChanged();
  }
}

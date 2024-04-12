OxideQQuickWebContext* OxideQQuickWebView::context() const {
  Q_D(const OxideQQuickWebView);

  QObject* c = d->contextHandle();
  if (!c) {
    return nullptr;
  }

  return qobject_cast<OxideQQuickWebContext*>(c);
}

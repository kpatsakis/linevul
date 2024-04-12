void OxideQQuickWebViewPrivate::CloseRequested() {
  Q_Q(OxideQQuickWebView);

  emit q->closeRequested();
}

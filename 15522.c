void OxideQQuickWebViewPrivate::LoadingChanged() {
  Q_Q(OxideQQuickWebView);

  emit q->loadingStateChanged();
}

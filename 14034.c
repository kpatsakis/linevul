void OxideQQuickWebView::setRestoreState(const QString& state) {
  Q_D(OxideQQuickWebView);

  if (d->proxy_) {
    qWarning() <<
        "OxideQQuickWebView: restoreState must be provided during construction";
    return;
  }

  d->construct_props_->restore_state =
      QByteArray::fromBase64(state.toLocal8Bit());
}

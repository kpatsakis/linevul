void QQuickWebViewPrivate::didSameDocumentNavigation()
{
    Q_Q(QQuickWebView);

    q->emitUrlChangeIfNeeded();
    emit q->navigationHistoryChanged();
}

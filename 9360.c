void QQuickWebViewPrivate::didChangeLoadingState(QWebLoadRequest* loadRequest)
{
    Q_Q(QQuickWebView);
    ASSERT(q->loading() == (loadRequest->status() == QQuickWebView::LoadStartedStatus));
    emit q->loadingChanged(loadRequest);
    m_loadStartedSignalSent = loadRequest->status() == QQuickWebView::LoadStartedStatus;
}

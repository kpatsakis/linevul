QUrl QQuickWebView::url() const
{
    Q_D(const QQuickWebView);


    return QUrl(d->m_currentUrl);
}

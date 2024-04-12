void QQuickWebView::setUrl(const QUrl& url)
{
    Q_D(QQuickWebView);

    if (url.isEmpty())
        return;

    if (!isComponentComplete()) {
        d->m_deferedUrlToLoad = url;
        return;
    }

    d->webPageProxy->loadURL(url.toString());
}

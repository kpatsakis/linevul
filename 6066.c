int QQuickWebViewExperimental::preferredMinimumContentsWidth() const
{
    Q_D(const QQuickWebView);
    return d->webPageProxy->pageGroup()->preferences()->layoutFallbackWidth();
}

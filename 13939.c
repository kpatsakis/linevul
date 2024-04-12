void QQuickWebViewExperimental::setUserAgent(const QString& userAgent)
{
    Q_D(QQuickWebView);
    if (userAgent == QString(d->webPageProxy->userAgent()))
        return;

    d->webPageProxy->setUserAgent(userAgent);
    emit userAgentChanged();
}

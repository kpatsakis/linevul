void QQuickWebView::goBack()
{
    Q_D(QQuickWebView);
    d->webPageProxy->goBack();
}

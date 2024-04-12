void QQuickWebViewPrivate::setNeedsDisplay()
{
    Q_Q(QQuickWebView);
    if (renderToOffscreenBuffer()) {
        QImage dummyImage(1, 1, QImage::Format_ARGB32);
        QPainter painter(&dummyImage);
        q->page()->d->paint(&painter);
        return;
    }

    q->page()->update();
}

void QQuickWebView::mousePressEvent(QMouseEvent* event)
{
    Q_D(QQuickWebView);
    forceActiveFocus();
    d->pageView->eventHandler()->handleMousePressEvent(event);
}

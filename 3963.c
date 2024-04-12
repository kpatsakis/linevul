void QQuickWebView::mouseDoubleClickEvent(QMouseEvent* event)
{
    Q_D(QQuickWebView);
    d->pageView->eventHandler()->handleMousePressEvent(event);
}

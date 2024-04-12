void QQuickWebViewAttached::setView(QQuickWebView* view)
{
    if (m_view == view)
        return;
    m_view = view;
    emit viewChanged();
}

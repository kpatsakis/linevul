QQuickWebView::QQuickWebView(QQuickItem* parent)
    : QQuickItem(parent)
    , d_ptr(createPrivateObject(this))
    , m_experimental(new QQuickWebViewExperimental(this))
{
    Q_D(QQuickWebView);
    d->initialize();
}

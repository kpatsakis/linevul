PassOwnPtr<DrawingAreaProxy> WebView::createDrawingAreaProxy()
{
    if (useNewDrawingArea())
        return DrawingAreaProxyImpl::create(m_page.get());

    return ChunkedUpdateDrawingAreaProxy::create(this, m_page.get());
}

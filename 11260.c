void FrameView::adjustViewSize()
{
    RenderView* renderView = this->renderView();
    if (!renderView)
        return;

    ASSERT(m_frame->view() == this);

    const IntRect rect = renderView->documentRect();
    const IntSize& size = rect.size();
    ScrollView::setScrollOrigin(IntPoint(-rect.x(), -rect.y()), !m_frame->document()->printing(), size == contentsSize());

    setContentsSize(size);
}

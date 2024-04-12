void FrameView::maintainScrollPositionAtAnchor(Node* anchorNode)
{
    m_maintainScrollPositionAnchor = anchorNode;
    if (!m_maintainScrollPositionAnchor)
        return;

    m_frame->document()->updateRenderTreeIfNeeded();
    RenderView* renderView = this->renderView();
    if (renderView && renderView->needsLayout())
        layout();
    else
        scrollToAnchor();
}

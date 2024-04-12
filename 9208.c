void FrameView::scrollToAnchor()
{
    RefPtrWillBeRawPtr<Node> anchorNode = m_maintainScrollPositionAnchor;
    if (!anchorNode)
        return;

    if (!anchorNode->renderer())
        return;

    LayoutRect rect;
    if (anchorNode != m_frame->document())
        rect = anchorNode->boundingBox();

    anchorNode->renderer()->scrollRectToVisible(rect, ScrollAlignment::alignToEdgeIfNeeded, ScrollAlignment::alignTopAlways);

    if (AXObjectCache* cache = m_frame->document()->existingAXObjectCache())
        cache->handleScrolledToAnchor(anchorNode.get());

    m_maintainScrollPositionAnchor = anchorNode;
}

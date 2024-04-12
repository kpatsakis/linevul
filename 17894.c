void Range::textRects(Vector<IntRect>& rects, bool useSelectionHeight, RangeInFixedPosition* inFixed)
{
    Node* startContainer = m_start.container();
    Node* endContainer = m_end.container();

    if (!startContainer || !endContainer) {
        if (inFixed)
            *inFixed = NotFixedPosition;
        return;
    }

    bool allFixed = true;
    bool someFixed = false;

    Node* stopNode = pastLastNode();
    for (Node* node = firstNode(); node != stopNode; node = node->traverseNextNode()) {
        RenderObject* r = node->renderer();
        if (!r || !r->isText())
            continue;
        RenderText* renderText = toRenderText(r);
        int startOffset = node == startContainer ? m_start.offset() : 0;
        int endOffset = node == endContainer ? m_end.offset() : numeric_limits<int>::max();
        bool isFixed = false;
        renderText->absoluteRectsForRange(rects, startOffset, endOffset, useSelectionHeight, &isFixed);
        allFixed &= isFixed;
        someFixed |= isFixed;
    }
    
    if (inFixed)
        *inFixed = allFixed ? EntirelyFixedPosition : (someFixed ? PartiallyFixedPosition : NotFixedPosition);
}

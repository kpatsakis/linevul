void RenderFlexibleBox::alignFlexLines(Vector<LineContext>& lineContexts)
{
    if (!isMultiline() || style()->alignContent() == AlignContentFlexStart)
        return;

    LayoutUnit availableCrossAxisSpace = crossAxisContentExtent();
    for (size_t i = 0; i < lineContexts.size(); ++i)
        availableCrossAxisSpace -= lineContexts[i].crossAxisExtent;

    RenderBox* child = m_orderIterator.first();
    LayoutUnit lineOffset = initialAlignContentOffset(availableCrossAxisSpace, style()->alignContent(), lineContexts.size());
    for (unsigned lineNumber = 0; lineNumber < lineContexts.size(); ++lineNumber) {
        lineContexts[lineNumber].crossAxisOffset += lineOffset;
        for (size_t childNumber = 0; childNumber < lineContexts[lineNumber].numberOfChildren; ++childNumber, child = m_orderIterator.next())
            adjustAlignmentForChild(child, lineOffset);

        if (style()->alignContent() == AlignContentStretch && availableCrossAxisSpace > 0)
            lineContexts[lineNumber].crossAxisExtent += availableCrossAxisSpace / static_cast<unsigned>(lineContexts.size());

        lineOffset += alignContentSpaceBetweenChildren(availableCrossAxisSpace, style()->alignContent(), lineContexts.size());
    }
}

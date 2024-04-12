void Scrollbar::setParent(ScrollView* parentView)
{
    if (!parentView && m_overlapsResizer && parent())
        parent()->adjustScrollbarsAvoidingResizerCount(-1);
    Widget::setParent(parentView);
}

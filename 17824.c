void Document::webkitWillEnterFullScreenForElement(Element* element)
{
    if (!attached() || inPageCache())
        return;

    ASSERT(element);

    if (!page())
        return;

    ASSERT(page()->settings()->fullScreenEnabled());

    if (m_fullScreenRenderer)
        m_fullScreenRenderer->unwrapRenderer();

    m_fullScreenElement = element;

#if USE(NATIVE_FULLSCREEN_VIDEO)
    if (element && element->isMediaElement())
        return;
#endif

    RenderObject* renderer = m_fullScreenElement->renderer();
    bool shouldCreatePlaceholder = renderer && renderer->isBox();
    if (shouldCreatePlaceholder) {
        m_savedPlaceholderFrameRect = toRenderBox(renderer)->frameRect();
        m_savedPlaceholderRenderStyle = RenderStyle::clone(renderer->style());
    }

    if (m_fullScreenElement != documentElement())
        RenderFullScreen::wrapRenderer(renderer, renderer ? renderer->parent() : 0, this);

    m_fullScreenElement->setContainsFullScreenElementOnAncestorsCrossingFrameBoundaries(true);
    
    recalcStyle(Force);
}

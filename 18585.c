void InspectorPageAgent::didPaint(RenderObject*, const GraphicsLayer*, GraphicsContext* context, const LayoutRect& rect)
{
    if (!m_enabled || m_client->overridesShowPaintRects() || !m_state->getBoolean(PageAgentState::pageAgentShowPaintRects))
        return;

    static int colorSelector = 0;
    const Color colors[] = {
        Color(0, 0x5F, 0, 0x3F),
        Color(0, 0xAF, 0, 0x3F),
        Color(0, 0xFF, 0, 0x3F),
    };

    LayoutRect inflatedRect(rect);
    inflatedRect.inflate(-1);
    m_overlay->drawOutline(context, inflatedRect, colors[colorSelector++ % WTF_ARRAY_LENGTH(colors)]);
}

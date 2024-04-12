bool SVGImage::hasRelativeWidth() const
{
    if (!m_page)
        return false;
    LocalFrame* frame = m_page->mainFrame();
    SVGSVGElement* rootElement = toSVGDocument(frame->document())->rootElement();
    if (!rootElement)
        return false;
    return rootElement->intrinsicWidth().isPercent();
}

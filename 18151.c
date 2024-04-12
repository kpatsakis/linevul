 AffineTransform LayoutSVGViewportContainer::viewportTransform() const
{
    ASSERT(element());
    if (isSVGSVGElement(*element())) {
        SVGSVGElement* svg = toSVGSVGElement(element());
        return svg->viewBoxToViewTransform(m_viewport.width(), m_viewport.height());
    }

    return AffineTransform();
}

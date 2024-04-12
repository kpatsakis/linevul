LayoutSVGViewportContainer::LayoutSVGViewportContainer(SVGElement* node)
    : LayoutSVGContainer(node)
    , m_isLayoutSizeChanged(false)
    , m_needsTransformUpdate(true)
{
}

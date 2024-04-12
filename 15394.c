LayoutUnit RenderBlockFlow::lowestFloatLogicalBottom(FloatingObject::Type floatType) const
{
    if (!m_floatingObjects)
        return 0;

    return m_floatingObjects->lowestFloatLogicalBottom(floatType);
}

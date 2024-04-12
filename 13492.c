void RenderBox::imageChanged(WrappedImagePtr image, const IntRect*)
{
    if (!parent())
        return;

    AllowRepaintScope scoper(frameView());

    if ((style()->borderImage().image() && style()->borderImage().image()->data() == image) ||
        (style()->maskBoxImage().image() && style()->maskBoxImage().image()->data() == image)) {
        repaint();
        return;
    }

    ShapeValue* shapeOutsideValue = style()->shapeOutside();
    if (!frameView()->isInPerformLayout() && isFloating() && shapeOutsideValue && shapeOutsideValue->image() && shapeOutsideValue->image()->data() == image) {
        ShapeOutsideInfo::ensureInfo(*this).markShapeAsDirty();
        markShapeOutsideDependentsForLayout();
    }

    bool didFullRepaint = repaintLayerRectsForImage(image, style()->backgroundLayers(), true);
    if (!didFullRepaint)
        repaintLayerRectsForImage(image, style()->maskLayers(), false);

    if (hasLayer() && layer()->hasCompositedMask() && layersUseImage(image, style()->maskLayers()))
        layer()->contentChanged(MaskImageChanged);
}

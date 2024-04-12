void RenderLayerScrollableArea::drawPlatformResizerImage(GraphicsContext* context, IntRect resizerCornerRect)
{
    float deviceScaleFactor = blink::deviceScaleFactor(box().frame());

    RefPtr<Image> resizeCornerImage;
    IntSize cornerResizerSize;
    if (deviceScaleFactor >= 2) {
        DEFINE_STATIC_REF(Image, resizeCornerImageHiRes, (Image::loadPlatformResource("textAreaResizeCorner@2x")));
        resizeCornerImage = resizeCornerImageHiRes;
        cornerResizerSize = resizeCornerImage->size();
        cornerResizerSize.scale(0.5f);
    } else {
        DEFINE_STATIC_REF(Image, resizeCornerImageLoRes, (Image::loadPlatformResource("textAreaResizeCorner")));
        resizeCornerImage = resizeCornerImageLoRes;
        cornerResizerSize = resizeCornerImage->size();
    }

    if (box().style()->shouldPlaceBlockDirectionScrollbarOnLogicalLeft()) {
        context->save();
        context->translate(resizerCornerRect.x() + cornerResizerSize.width(), resizerCornerRect.y() + resizerCornerRect.height() - cornerResizerSize.height());
        context->scale(-1.0, 1.0);
        context->drawImage(resizeCornerImage.get(), IntRect(IntPoint(), cornerResizerSize));
        context->restore();
        return;
    }
    IntRect imageRect(resizerCornerRect.maxXMaxYCorner() - cornerResizerSize, cornerResizerSize);
    context->drawImage(resizeCornerImage.get(), imageRect);
}

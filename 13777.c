void drawRect(GraphicsContext& context, const TestDisplayItemClient& client, DisplayItem::Type type, const FloatRect& bounds)
{
    if (DrawingRecorder::useCachedDrawingIfPossible(context, client, type))
        return;
    DrawingRecorder drawingRecorder(context, client, type, bounds);
    IntRect rect(0, 0, 10, 10);
    context.drawRect(rect);
}

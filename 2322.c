ScriptPromise ImageBitmapFactories::createImageBitmap(EventTarget& eventTarget, HTMLCanvasElement* canvas, ExceptionState& exceptionState)
{
    return createImageBitmap(eventTarget, canvas, 0, 0, canvas->width(), canvas->height(), exceptionState);
}

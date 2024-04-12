ScriptPromise ImageBitmapFactories::createImageBitmap(EventTarget& eventTarget, ImageBitmap* bitmap, int sx, int sy, int sw, int sh, ExceptionState& exceptionState)
{
    if (!bitmap) {
        exceptionState.throwTypeError("The ImageBitmap provided is invalid.");
        return ScriptPromise();
    }
    if (!sw || !sh) {
        exceptionState.throwDOMException(IndexSizeError, String::format("The source %s provided is 0.", sw ? "height" : "width"));
        return ScriptPromise();
    }
    return fulfillImageBitmap(eventTarget.executionContext(), ImageBitmap::create(bitmap, IntRect(sx, sy, sw, sh)));
}

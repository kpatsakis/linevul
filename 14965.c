static void dumpDescendantFramesText(WKBundleFrameRef frame, StringBuilder& stringBuilder)
{
    WKRetainPtr<WKArrayRef> childFrames(AdoptWK, WKBundleFrameCopyChildFrames(frame));
    size_t size = WKArrayGetSize(childFrames.get());
    for (size_t i = 0; i < size; ++i) {
        WKBundleFrameRef subframe = static_cast<WKBundleFrameRef>(WKArrayGetItemAtIndex(childFrames.get(), i));
        WKRetainPtr<WKStringRef> subframeName(AdoptWK, WKBundleFrameCopyName(subframe));

        stringBuilder.appendLiteral("\n--------\nFrame: '");
        stringBuilder.append(toWTFString(subframeName));
        stringBuilder.appendLiteral("'\n--------\n");

        dumpFrameText(subframe, stringBuilder);
        dumpDescendantFramesText(subframe, stringBuilder);
    }
}

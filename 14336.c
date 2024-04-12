void TokenPreloadScanner::scan(const HTMLToken& token, const SegmentedString& source, PreloadRequestStream& requests, ViewportDescriptionWrapper* viewport)
{
    scanCommon(token, source, requests, viewport, nullptr);
}

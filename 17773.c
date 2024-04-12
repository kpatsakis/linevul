void WebPagePrivate::notifyFlushRequired(const GraphicsLayer*)
{
    scheduleRootLayerCommit();
}

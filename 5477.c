void InjectedBundlePage::didFinishLoadForFrame(WKBundleFrameRef frame)
{
    if (!InjectedBundle::shared().isTestRunning())
        return;

    if (InjectedBundle::shared().testRunner()->shouldDumpFrameLoadCallbacks())
        dumpLoadEvent(frame, "didFinishLoadForFrame");

    frameDidChangeLocation(frame, /*shouldDump*/ true);
}

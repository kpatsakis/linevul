void InjectedBundlePage::didReceiveServerRedirectForProvisionalLoadForFrame(WKBundleFrameRef frame)
{
    if (!InjectedBundle::shared().isTestRunning())
        return;

    if (!InjectedBundle::shared().testRunner()->shouldDumpFrameLoadCallbacks())
        return;

    dumpLoadEvent(frame, "didReceiveServerRedirectForProvisionalLoadForFrame");
}

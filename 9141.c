bool InjectedBundlePage::supportsFullScreen(WKBundlePageRef pageRef, WKFullScreenKeyboardRequestType requestType)
{
    if (InjectedBundle::shared().testRunner()->shouldDumpFullScreenCallbacks())
        InjectedBundle::shared().outputText("supportsFullScreen() == true\n");
    return true;
}

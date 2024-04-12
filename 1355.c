static void didReceiveServerRedirectForProvisionalLoadForFrame(WKPageRef page, WKFrameRef frame, WKTypeRef userData, const void* clientInfo)
{
    if (!WKFrameIsMainFrame(frame))
        return;

    webkitWebViewLoadChanged(WEBKIT_WEB_VIEW(clientInfo), WEBKIT_LOAD_REDIRECTED);
}

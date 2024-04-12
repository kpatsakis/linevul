static void didSameDocumentNavigationForFrame(WKPageRef page, WKFrameRef frame, WKSameDocumentNavigationType, WKTypeRef, const void* clientInfo)
{
    if (!WKFrameIsMainFrame(frame))
        return;

    webkitWebViewUpdateURI(WEBKIT_WEB_VIEW(clientInfo));
}

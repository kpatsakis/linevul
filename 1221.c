static void toplevelWindowResizeGripVisibilityChanged(GObject* object, GParamSpec*, WebKitWebViewBase* webViewBase)
{
    webkitWebViewBaseNotifyResizerSizeForWindow(webViewBase, GTK_WINDOW(object));
}

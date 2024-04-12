void webkitWebViewBaseCreateWebPage(WebKitWebViewBase* webkitWebViewBase, WKContextRef context, WKPageGroupRef pageGroup)
{
    WebKitWebViewBasePrivate* priv = webkitWebViewBase->priv;

    priv->pageProxy = toImpl(context)->createWebPage(priv->pageClient.get(), toImpl(pageGroup));
    priv->pageProxy->initializeWebPage();

#if ENABLE(FULLSCREEN_API)
    priv->pageProxy->fullScreenManager()->setWebView(webkitWebViewBase);
#endif
}

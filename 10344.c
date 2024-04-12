QQuickWebViewFlickablePrivate::QQuickWebViewFlickablePrivate(QQuickWebView* viewport)
    : QQuickWebViewPrivate(viewport)
    , postTransitionState(adoptPtr(new PostTransitionState(this)))
    , isTransitioningToNewPage(false)
    , pageIsSuspended(true)
    , loadSuccessDispatchIsPending(false)
{
}

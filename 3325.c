NavigatorServiceWorker& NavigatorServiceWorker::from(Navigator& navigator)
{
    NavigatorServiceWorker* supplement = toNavigatorServiceWorker(navigator);
    if (!supplement) {
        supplement = new NavigatorServiceWorker(navigator);
        provideTo(navigator, supplementName(), supplement);
        if (navigator.frame() && navigator.frame()->securityContext()->securityOrigin()->canAccessServiceWorkers()) {
            supplement->serviceWorker(ASSERT_NO_EXCEPTION);
        }
    }
    return *supplement;
}

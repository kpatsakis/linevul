void WebContentsImpl::DetachInterstitialPage() {
  if (GetInterstitialPage())
    GetRenderManager()->remove_interstitial_page();
  FOR_EACH_OBSERVER(WebContentsObserver, observers_,
                    DidDetachInterstitialPage());
}

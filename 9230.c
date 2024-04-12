    WebContentsImpl::GetOrCreateRootBrowserAccessibilityManager() {
  RenderFrameHostImpl* rfh = static_cast<RenderFrameHostImpl*>(
      ShowingInterstitialPage() ? GetInterstitialPage()->GetMainFrame()
                                : GetMainFrame());
  return rfh ? rfh->GetOrCreateBrowserAccessibilityManager() : nullptr;
}

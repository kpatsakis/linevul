  SafeBrowsingBlockingPage* GetSafeBrowsingBlockingPage() {
    InterstitialPage* interstitial =
        InterstitialPage::GetInterstitialPage(contents());
    if (!interstitial)
      return NULL;
    return  static_cast<SafeBrowsingBlockingPage*>(interstitial);
  }

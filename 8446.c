  virtual void TestInterstitialPageDeleted(TestInterstitialPage* interstitial) {
    DCHECK(interstitial_page_ == interstitial);
    interstitial_page_ = NULL;
  }

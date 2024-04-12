  void SendInterstitialCommand(
      content::WebContents* tab,
      security_interstitials::SecurityInterstitialCommand command) {
    if (AreCommittedInterstitialsEnabled()) {
      security_interstitials::SecurityInterstitialTabHelper* helper =
          security_interstitials::SecurityInterstitialTabHelper::
              FromWebContents(tab);
      helper->GetBlockingPageForCurrentlyCommittedNavigationForTesting()
          ->CommandReceived(base::IntToString(command));
      return;
    }
    tab->GetInterstitialPage()->GetDelegateForTesting()->CommandReceived(
        base::IntToString(command));
  }

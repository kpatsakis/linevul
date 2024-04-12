  void SendCommand(const std::string& command) {
    TabContents* contents = browser()->GetSelectedTabContents();
    SafeBrowsingBlockingPage* interstitial_page =
        static_cast<SafeBrowsingBlockingPage*>(
            InterstitialPage::GetInterstitialPage(contents));
    ASSERT_TRUE(interstitial_page);
    interstitial_page->CommandReceived(command);
  }

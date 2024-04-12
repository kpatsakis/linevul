  TestInterstitialPage(TabContents* tab,
                       bool new_navigation,
                       const GURL& url,
                       InterstitialState* state,
                       bool* deleted)
      : InterstitialPageImpl(
            tab, new_navigation, url,
            new TestInterstitialPageDelegate(this)),
        state_(state),
        deleted_(deleted),
        command_received_count_(0),
        delegate_(NULL) {
    *state_ = UNDECIDED;
    *deleted_ = false;
  }

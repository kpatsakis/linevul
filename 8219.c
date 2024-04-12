  TestOfflineLoadPage(TabContents* tab_contents,
                      const GURL& url,
                      OfflineLoadPageTest* test_page)
    : chromeos::OfflineLoadPage(tab_contents, url, CompletionCallback()),
      test_page_(test_page) {
    interstitial_page_->DontCreateViewForTesting();
  }

  base::Process ShowSingletonTab(const GURL& page) {
    ::ShowSingletonTab(browser(), page);
    WebContents* wc = browser()->tab_strip_model()->GetActiveWebContents();
    CHECK(wc->GetURL() == page);

    WaitForLauncherThread();
    WaitForMessageProcessing(wc);
    return ProcessFromHandle(
        wc->GetMainFrame()->GetProcess()->GetProcess().Handle());
  }

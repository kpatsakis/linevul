void InProcessBrowserTest::AddTabAtIndexToBrowser(
    Browser* browser,
    int index,
    const GURL& url,
    content::PageTransition transition) {
  chrome::NavigateParams params(browser, url, transition);
  params.tabstrip_index = index;
  params.disposition = NEW_FOREGROUND_TAB;
  chrome::Navigate(&params);

  content::WaitForLoadStop(params.target_contents);
}

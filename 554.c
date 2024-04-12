InterstitialPage* InterstitialPage::GetInterstitialPage(
    WebContents* web_contents) {
  InitInterstitialPageMap();
  InterstitialPageMap::const_iterator iter =
      g_web_contents_to_interstitial_page->find(web_contents);
  if (iter == g_web_contents_to_interstitial_page->end())
    return NULL;

  return iter->second;
}

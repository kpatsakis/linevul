void DefaultBindingsDelegate::OpenInNewTab(const std::string& url) {
  content::OpenURLParams params(GURL(url), content::Referrer(),
                                WindowOpenDisposition::NEW_FOREGROUND_TAB,
                                ui::PAGE_TRANSITION_LINK, false);
  Browser* browser = FindBrowser(web_contents_);
  browser->OpenURL(params);
}

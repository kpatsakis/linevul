void BrowserWindowGtk::ShowPageInfo(content::WebContents* web_contents,
                                    const GURL& url,
                                    const SSLStatus& ssl,
                                    bool show_history) {
  chrome::ShowPageInfoBubble(window_, web_contents, url, ssl, show_history,
                             browser_.get());
}

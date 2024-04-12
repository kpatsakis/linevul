    ChromeContentBrowserClient::GetCryptoPasswordDelegate(
        const GURL& url) {
  return browser::NewCryptoModuleBlockingDialogDelegate(
      browser::kCryptoModulePasswordKeygen, url.host());
}

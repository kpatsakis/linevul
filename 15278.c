const GURL& ChromePaymentRequestDelegate::GetLastCommittedURL() const {
  return web_contents_->GetLastCommittedURL();
}

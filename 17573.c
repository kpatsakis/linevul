bool ChromePaymentRequestDelegate::IsIncognito() const {
  Profile* profile =
      Profile::FromBrowserContext(web_contents_->GetBrowserContext());
  return profile && profile->GetProfileType() == Profile::INCOGNITO_PROFILE;
}

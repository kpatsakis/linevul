ChromeExtensionsAPIClient::CreateGuestViewManagerDelegate(
    content::BrowserContext* context) const {
  return base::MakeUnique<ChromeGuestViewManagerDelegate>(context);
}

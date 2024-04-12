SiteProcessMap* GetSiteProcessMapForBrowserContext(BrowserContext* context) {
  DCHECK(context);
  SiteProcessMap* map = static_cast<SiteProcessMap*>(
      context->GetUserData(kSiteProcessMapKeyName));
  if (!map) {
    map = new SiteProcessMap();
    context->SetUserData(kSiteProcessMapKeyName, base::WrapUnique(map));
  }
  return map;
}

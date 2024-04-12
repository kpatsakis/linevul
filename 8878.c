bool RenderFrameHostManager::IsCurrentlySameSite(RenderFrameHostImpl* candidate,
                                                 const GURL& dest_url) {
  BrowserContext* browser_context =
      delegate_->GetControllerForRenderManager().GetBrowserContext();

  if (candidate->GetSiteInstance()->HasWrongProcessForURL(dest_url))
    return false;

  if (candidate->last_successful_url().is_empty()) {
    return SiteInstance::IsSameWebSite(
        browser_context, candidate->GetSiteInstance()->GetSiteURL(), dest_url);
  }

  if (SiteInstance::IsSameWebSite(browser_context,
                                  candidate->last_successful_url(), dest_url)) {
    return true;
  }

  if (!candidate->GetLastCommittedOrigin().unique() &&
      SiteInstance::IsSameWebSite(
          browser_context,
          GURL(candidate->GetLastCommittedOrigin().Serialize()), dest_url)) {
    return true;
  }

  return false;
}

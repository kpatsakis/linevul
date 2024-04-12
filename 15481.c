double WebContentsImpl::GetPendingPageZoomLevel() {
  NavigationEntry* pending_entry = GetController().GetPendingEntry();
  if (!pending_entry)
    return HostZoomMap::GetZoomLevel(this);

  GURL url = pending_entry->GetURL();
  return HostZoomMap::GetForWebContents(this)->GetZoomLevelForHostAndScheme(
      url.scheme(), net::GetHostOrSpecFromURL(url));
}

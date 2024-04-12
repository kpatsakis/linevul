void WebContentsImpl::UpdateZoomIfNecessary(const std::string& scheme,
                                            const std::string& host,
                                            double level) {
  NavigationEntry* entry = GetController().GetLastCommittedEntry();
  if (!entry)
    return;

  GURL url = HostZoomMap::GetURLFromEntry(entry);
  if (host != net::GetHostOrSpecFromURL(url) ||
      (!scheme.empty() && !url.SchemeIs(scheme))) {
    return;
  }

  UpdateZoom(level);
}

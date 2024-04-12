void WebContentsImpl::UpdateState(RenderViewHost* rvh,
                                  int32_t page_id,
                                  const PageState& page_state) {
  DCHECK(!SiteIsolationPolicy::UseSubframeNavigationEntries());

  if (rvh->GetDelegate()->GetAsWebContents() != this)
    return;

  RenderViewHostImpl* rvhi = static_cast<RenderViewHostImpl*>(rvh);
  NavigationEntryImpl* entry = controller_.GetEntryWithPageID(
      rvhi->GetSiteInstance(), page_id);
  if (!entry)
    return;

  if (rvhi->GetMainFrame()) {
    NavigationEntryImpl* new_entry = controller_.GetEntryWithUniqueID(
        static_cast<RenderFrameHostImpl*>(rvhi->GetMainFrame())
            ->nav_entry_id());

    DCHECK_EQ(entry, new_entry);
  }

  if (page_state == entry->GetPageState())
    return;  // Nothing to update.
  entry->SetPageState(page_state);
  controller_.NotifyEntryChanged(entry);
}

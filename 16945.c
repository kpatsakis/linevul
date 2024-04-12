void NavigationController::RendererDidNavigateInPage(
    const ViewHostMsg_FrameNavigate_Params& params, bool* did_replace_entry) {
  DCHECK(content::PageTransitionIsMainFrame(params.transition)) <<
      "WebKit should only tell us about in-page navs for the main frame.";
  NavigationEntry* existing_entry = GetEntryWithPageID(
      tab_contents_->GetSiteInstance(),
      params.page_id);

  existing_entry->set_url(params.url);
  if (existing_entry->update_virtual_url_with_url())
    UpdateVirtualURLToURL(existing_entry, params.url);

  *did_replace_entry = true;

  if (pending_entry_)
    DiscardNonCommittedEntriesInternal();

  last_committed_entry_index_ =
      GetEntryIndexWithPageID(tab_contents_->GetSiteInstance(), params.page_id);
}

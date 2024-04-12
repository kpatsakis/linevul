NavigationType NavigationControllerImpl::ClassifyNavigation(
    const ViewHostMsg_FrameNavigate_Params& params) const {
  if (params.page_id == -1) {
    return NAVIGATION_TYPE_NAV_IGNORE;
  }

  if (params.page_id > web_contents_->GetMaxPageID()) {
    if (PageTransitionIsMainFrame(params.transition))
      return NAVIGATION_TYPE_NEW_PAGE;

    if (!GetLastCommittedEntry())
      return NAVIGATION_TYPE_NAV_IGNORE;

    return NAVIGATION_TYPE_NEW_SUBFRAME;
  }

  DCHECK(!params.history_list_was_cleared);

  int existing_entry_index = GetEntryIndexWithPageID(
      web_contents_->GetSiteInstance(),
      params.page_id);
  if (existing_entry_index == -1) {
    NOTREACHED();

    LOG(ERROR) << "terminating renderer for bad navigation: " << params.url;
    RecordAction(UserMetricsAction("BadMessageTerminate_NC"));

    std::string temp = params.url.spec();
    temp.append("#page");
    temp.append(base::IntToString(params.page_id));
    temp.append("#max");
    temp.append(base::IntToString(web_contents_->GetMaxPageID()));
    temp.append("#frame");
    temp.append(base::IntToString(params.frame_id));
    temp.append("#ids");
    for (int i = 0; i < static_cast<int>(entries_.size()); ++i) {
      temp.append(base::IntToString(entries_[i]->GetPageID()));
      temp.append("_");
      if (entries_[i]->site_instance())
        temp.append(base::IntToString(entries_[i]->site_instance()->GetId()));
      else
        temp.append("N");
      if (entries_[i]->site_instance() != web_contents_->GetSiteInstance())
        temp.append("x");
      temp.append(",");
    }
    GURL url(temp);
    static_cast<RenderViewHostImpl*>(
        web_contents_->GetRenderViewHost())->Send(
            new ViewMsg_TempCrashWithData(url));
    return NAVIGATION_TYPE_NAV_IGNORE;
  }
  NavigationEntryImpl* existing_entry = entries_[existing_entry_index].get();

  if (!PageTransitionIsMainFrame(params.transition)) {
    DCHECK(GetLastCommittedEntry());
    return NAVIGATION_TYPE_AUTO_SUBFRAME;
  }

  if (pending_entry_ &&
      !pending_entry_->is_renderer_initiated() &&
      existing_entry != pending_entry_ &&
      pending_entry_->GetPageID() == -1 &&
      existing_entry == GetLastCommittedEntry()) {
    return NAVIGATION_TYPE_SAME_PAGE;
  }

  if (AreURLsInPageNavigation(existing_entry->GetURL(), params.url,
                              params.was_within_same_page,
                              NAVIGATION_TYPE_UNKNOWN)) {
    return NAVIGATION_TYPE_IN_PAGE;
  }

  return NAVIGATION_TYPE_EXISTING_PAGE;
}

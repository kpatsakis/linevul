void NavigationController::RendererDidNavigateToNewPage(
    const ViewHostMsg_FrameNavigate_Params& params, bool* did_replace_entry) {
  NavigationEntry* new_entry;
  if (pending_entry_) {
    new_entry = new NavigationEntry(*pending_entry_);

    new_entry->set_page_type(NavigationEntry::NORMAL_PAGE);
  } else {
    new_entry = new NavigationEntry;
  }

  new_entry->set_url(params.url);
  new_entry->set_referrer(params.referrer);
  new_entry->set_page_id(params.page_id);
  new_entry->set_transition_type(params.transition);
  new_entry->set_site_instance(tab_contents_->GetSiteInstance());
  new_entry->set_has_post_data(params.is_post);

  *did_replace_entry = IsRedirect(params) &&
                       IsLikelyAutoNavigation(base::TimeTicks::Now());
  InsertOrReplaceEntry(new_entry, *did_replace_entry);
}

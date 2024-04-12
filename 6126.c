NavigationControllerImpl::CreateNavigationRequest(
    FrameTreeNode* frame_tree_node,
    const NavigationEntryImpl& entry,
    FrameNavigationEntry* frame_entry,
    ReloadType reload_type,
    bool is_same_document_history_load,
    bool is_history_navigation_in_new_child,
    const scoped_refptr<network::ResourceRequestBody>& post_body,
    std::unique_ptr<NavigationUIData> navigation_ui_data) {
  GURL dest_url = frame_entry->url();
  Referrer dest_referrer = frame_entry->referrer();
  if ((reload_type == ReloadType::ORIGINAL_REQUEST_URL ||
       reload_type == ReloadType::DISABLE_PREVIEWS) &&
      entry.GetOriginalRequestURL().is_valid() && !entry.GetHasPostData()) {
    dest_url = entry.GetOriginalRequestURL();
    dest_referrer = Referrer();
  }

  if (frame_tree_node->IsMainFrame()) {
    const GURL& virtual_url = entry.GetVirtualURL();
    if (!virtual_url.is_valid() && !virtual_url.is_empty()) {
      LOG(WARNING) << "Refusing to load for invalid virtual URL: "
                   << virtual_url.possibly_invalid_spec();
      return nullptr;
    }
  }

  if (!dest_url.is_valid() && !dest_url.is_empty()) {
    LOG(WARNING) << "Refusing to load invalid URL: "
                 << dest_url.possibly_invalid_spec();
    return nullptr;
  }

  if (dest_url.spec().size() > url::kMaxURLChars) {
    LOG(WARNING) << "Refusing to load URL as it exceeds " << url::kMaxURLChars
                 << " characters.";
    return nullptr;
  }

  PreviewsState previews_state = PREVIEWS_UNSPECIFIED;
  if (!frame_tree_node->IsMainFrame()) {
    previews_state = frame_tree_node->frame_tree()
                         ->root()
                         ->current_frame_host()
                         ->last_navigation_previews_state();
  } else if (reload_type == ReloadType::DISABLE_PREVIEWS) {
    previews_state = PREVIEWS_NO_TRANSFORM;
  }

  if (delegate_)
    delegate_->AdjustPreviewsStateForNavigation(&previews_state);

  base::TimeTicks navigation_start = base::TimeTicks::Now();
  TRACE_EVENT_INSTANT_WITH_TIMESTAMP0(
      "navigation,rail", "NavigationTiming navigationStart",
      TRACE_EVENT_SCOPE_GLOBAL, navigation_start);

  FrameMsg_Navigate_Type::Value navigation_type = GetNavigationType(
      frame_tree_node->current_url(),  // old_url
      dest_url,                        // new_url
      reload_type,                     // reload_type
      entry,                           // entry
      *frame_entry,                    // frame_entry
      is_same_document_history_load);  // is_same_document_history_load
  return NavigationRequest::CreateBrowserInitiated(
      frame_tree_node, dest_url, dest_referrer, *frame_entry, entry,
      navigation_type, previews_state, is_same_document_history_load,
      is_history_navigation_in_new_child, post_body, navigation_start, this,
      std::move(navigation_ui_data));
}

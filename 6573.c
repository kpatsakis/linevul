FrameMsg_Navigate_Type::Value GetNavigationType(
    const GURL& old_url,
    const GURL& new_url,
    ReloadType reload_type,
    const NavigationEntryImpl& entry,
    const FrameNavigationEntry& frame_entry,
    bool is_same_document_history_load) {
  switch (reload_type) {
    case ReloadType::NORMAL:
      return FrameMsg_Navigate_Type::RELOAD;
    case ReloadType::BYPASSING_CACHE:
    case ReloadType::DISABLE_PREVIEWS:
      return FrameMsg_Navigate_Type::RELOAD_BYPASSING_CACHE;
    case ReloadType::ORIGINAL_REQUEST_URL:
      return FrameMsg_Navigate_Type::RELOAD_ORIGINAL_REQUEST_URL;
    case ReloadType::NONE:
      break;  // Fall through to rest of function.
  }

  if (entry.restore_type() == RestoreType::LAST_SESSION_EXITED_CLEANLY) {
    if (entry.GetHasPostData())
      return FrameMsg_Navigate_Type::RESTORE_WITH_POST;
    else
      return FrameMsg_Navigate_Type::RESTORE;
  }

  if (frame_entry.page_state().IsValid()) {
    if (is_same_document_history_load)
      return FrameMsg_Navigate_Type::HISTORY_SAME_DOCUMENT;
    else
      return FrameMsg_Navigate_Type::HISTORY_DIFFERENT_DOCUMENT;
  }
  DCHECK(!is_same_document_history_load);

  if (new_url.has_ref() && old_url.EqualsIgnoringRef(new_url) &&
      frame_entry.method() == "GET") {
    return FrameMsg_Navigate_Type::SAME_DOCUMENT;
  } else {
    return FrameMsg_Navigate_Type::DIFFERENT_DOCUMENT;
  }
}

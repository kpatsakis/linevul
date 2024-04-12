WebFrameLoadType NavigationTypeToLoadType(
    FrameMsg_Navigate_Type::Value navigation_type,
    bool should_replace_current_entry,
    bool has_valid_page_state) {
  switch (navigation_type) {
    case FrameMsg_Navigate_Type::RELOAD:
    case FrameMsg_Navigate_Type::RELOAD_ORIGINAL_REQUEST_URL:
      return WebFrameLoadType::kReload;

    case FrameMsg_Navigate_Type::RELOAD_BYPASSING_CACHE:
      return WebFrameLoadType::kReloadBypassingCache;

    case FrameMsg_Navigate_Type::HISTORY_SAME_DOCUMENT:
    case FrameMsg_Navigate_Type::HISTORY_DIFFERENT_DOCUMENT:
      return WebFrameLoadType::kBackForward;

    case FrameMsg_Navigate_Type::RESTORE:
    case FrameMsg_Navigate_Type::RESTORE_WITH_POST:
      if (has_valid_page_state)
        return WebFrameLoadType::kBackForward;
      FALLTHROUGH;

    case FrameMsg_Navigate_Type::SAME_DOCUMENT:
    case FrameMsg_Navigate_Type::DIFFERENT_DOCUMENT:
      return should_replace_current_entry
                 ? WebFrameLoadType::kReplaceCurrentItem
                 : WebFrameLoadType::kStandard;

    default:
      NOTREACHED();
      return WebFrameLoadType::kStandard;
  }
}

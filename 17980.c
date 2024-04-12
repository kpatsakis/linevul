void UpdateLoadFlagsWithCacheFlags(
    int* load_flags,
    FrameMsg_Navigate_Type::Value navigation_type,
    bool is_post) {
  switch (navigation_type) {
    case FrameMsg_Navigate_Type::RELOAD:
    case FrameMsg_Navigate_Type::RELOAD_ORIGINAL_REQUEST_URL:
      *load_flags |= net::LOAD_VALIDATE_CACHE;
      break;
    case FrameMsg_Navigate_Type::RELOAD_BYPASSING_CACHE:
      *load_flags |= net::LOAD_BYPASS_CACHE;
      break;
    case FrameMsg_Navigate_Type::RESTORE:
      *load_flags |= net::LOAD_SKIP_CACHE_VALIDATION;
      break;
    case FrameMsg_Navigate_Type::RESTORE_WITH_POST:
      *load_flags |=
          net::LOAD_ONLY_FROM_CACHE | net::LOAD_SKIP_CACHE_VALIDATION;
      break;
    case FrameMsg_Navigate_Type::SAME_DOCUMENT:
    case FrameMsg_Navigate_Type::DIFFERENT_DOCUMENT:
      if (is_post)
        *load_flags |= net::LOAD_VALIDATE_CACHE;
      break;
    case FrameMsg_Navigate_Type::HISTORY_SAME_DOCUMENT:
    case FrameMsg_Navigate_Type::HISTORY_DIFFERENT_DOCUMENT:
      if (is_post) {
        *load_flags |=
            net::LOAD_ONLY_FROM_CACHE | net::LOAD_SKIP_CACHE_VALIDATION;
      } else {
        *load_flags |= net::LOAD_SKIP_CACHE_VALIDATION;
      }
      break;
  }
}

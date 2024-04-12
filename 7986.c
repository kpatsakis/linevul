  explicit LoadCommittedDetailsObserver(WebContents* web_contents)
      : WebContentsObserver(web_contents),
        navigation_type_(NAVIGATION_TYPE_UNKNOWN),
        is_same_document_(false),
        is_main_frame_(false),
        did_replace_entry_(false) {}

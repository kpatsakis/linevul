  explicit FirstVisuallyNonEmptyPaintObserver(Shell* shell)
      : WebContentsObserver(shell->web_contents()),
        did_fist_visually_non_empty_paint_(false) {}

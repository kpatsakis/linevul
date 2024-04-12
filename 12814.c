BrowserRootView::BrowserRootView(BrowserView* browser_view,
                                 views::Widget* widget)
    : views::internal::RootView(widget),
      browser_view_(browser_view),
      forwarding_to_tab_strip_(false) { }

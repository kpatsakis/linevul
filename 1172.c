  TestBrowsingInstance(BrowserContext* browser_context, int* delete_counter)
      : BrowsingInstance(browser_context),
        delete_counter_(delete_counter) {
  }

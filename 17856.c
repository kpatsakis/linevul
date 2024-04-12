  AutofillDownloadTestHelper()
      : download_manager(&profile),
        request_context_getter(new TestURLRequestContextGetter()) {
    download_manager.SetObserver(this);
  }

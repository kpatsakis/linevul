  explicit TestSafeBrowsingService(const SafeBrowsingTestConfiguration* config)
      : test_configuration_(config) {
    services_delegate_ =
        safe_browsing::ServicesDelegate::CreateForTest(this, this);
  }

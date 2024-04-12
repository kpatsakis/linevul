std::unique_ptr<KeyedService> BuildMockDataStoreForContext(
    content::BrowserContext* browser_context) {
  return std::make_unique<MockDataStore>();
 }

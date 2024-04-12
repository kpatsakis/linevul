ProfileKeyedAPIFactory<BookmarksAPI>* BookmarksAPI::GetFactoryInstance() {
  return &g_factory.Get();
}

void FetchManager::OnLoaderFinished(Loader* loader) {
  loaders_.erase(loader);
  loader->Dispose();
}

DocumentLoadTiming* PerformanceNavigationTiming::GetDocumentLoadTiming() const {
  DocumentLoader* loader = GetDocumentLoader();
  if (!loader)
    return nullptr;

  return &loader->GetTiming();
}

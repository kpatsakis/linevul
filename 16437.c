    LRUCanvasResourceProviderCache::GetCanvasResourceProvider(
        const IntSize& size) {
  wtf_size_t i;
  for (i = 0; i < resource_providers_.size(); ++i) {
    CanvasResourceProvider* resource_provider = resource_providers_[i].get();
    if (!resource_provider)
      break;
    if (resource_provider->Size() != size)
      continue;
    BubbleToFront(i);
    return resource_provider;
  }

  std::unique_ptr<CanvasResourceProvider> temp(CanvasResourceProvider::Create(
      size, CanvasResourceProvider::kSoftwareResourceUsage,
      nullptr,              // context_provider_wrapper
      0,                    // msaa_sample_count,
      CanvasColorParams(),  // TODO: should this use the canvas's colorspace?
      CanvasResourceProvider::kDefaultPresentationMode,
      nullptr));  // canvas_resource_dispatcher
  if (!temp)
    return nullptr;
  i = std::min(resource_providers_.size() - 1, i);
  resource_providers_[i] = std::move(temp);

  CanvasResourceProvider* resource_provider = resource_providers_[i].get();
  BubbleToFront(i);
  return resource_provider;
}

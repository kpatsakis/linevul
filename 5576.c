static bool HasTextContent(Resource* cached_resource) {
  Resource::Type type = cached_resource->GetType();
  return type == Resource::kCSSStyleSheet || type == Resource::kXSLStyleSheet ||
         type == Resource::kScript || type == Resource::kRaw ||
         type == Resource::kImportResource || type == Resource::kMainResource;
}

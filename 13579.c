bool LoadingDataCollector::IsHandledResourceType(
    content::ResourceType resource_type,
    const std::string& mime_type) {
  content::ResourceType actual_resource_type =
      GetResourceType(resource_type, mime_type);
  return actual_resource_type == content::ResourceType::kMainFrame ||
         actual_resource_type == content::ResourceType::kStylesheet ||
         actual_resource_type == content::ResourceType::kScript ||
         actual_resource_type == content::ResourceType::kImage ||
         actual_resource_type == content::ResourceType::kFontResource;
}

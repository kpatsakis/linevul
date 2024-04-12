ImageLoader::ImageLoader(Element* element)
    : element_(element),
      image_complete_(true),
      loading_image_document_(false),
      suppress_error_events_(false) {
  RESOURCE_LOADING_DVLOG(1) << "new ImageLoader " << this;
}

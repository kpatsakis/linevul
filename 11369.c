String HTMLMediaElement::preload() const {
  return preloadTypeToString(preloadType());
}

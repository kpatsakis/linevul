DEFINE_TRACE(ImageLoader) {
  visitor->trace(m_image);
  visitor->trace(m_imageResourceForImageDocument);
  visitor->trace(m_element);
}

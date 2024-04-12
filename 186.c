bool ImageBitmap::isAccelerated() const {
  return m_image && (m_image->isTextureBacked() || m_image->hasMailbox());
}

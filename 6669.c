String PresentationConnection::binaryType() const {
  switch (m_binaryType) {
    case BinaryTypeBlob:
      return "blob";
    case BinaryTypeArrayBuffer:
      return "arraybuffer";
  }
  ASSERT_NOT_REACHED();
  return String();
}

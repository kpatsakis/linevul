void Document::CloneDataFromDocument(const Document& other) {
  SetCompatibilityMode(other.GetCompatibilityMode());
  SetEncodingData(other.encoding_data_);
  SetContextFeatures(other.GetContextFeatures());
  SetSecurityOrigin(other.GetSecurityOrigin()->IsolatedCopy());
  SetMimeType(other.contentType());
}

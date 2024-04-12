void Document::cloneDataFromDocument(const Document& other)
{
    setCompatibilityMode(other.getCompatibilityMode());
    setEncodingData(other.m_encodingData);
    setContextFeatures(other.contextFeatures());
    setSecurityOrigin(other.getSecurityOrigin()->isolatedCopy());
    setMimeType(other.contentType());
}

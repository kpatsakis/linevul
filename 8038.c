SVGDocumentExtensions::SVGDocumentExtensions(Document* document)
    : m_document(document)
    , m_resourcesCache(adoptPtr(new SVGResourcesCache))
#if !ASSERT_DISABLED
    , m_inRelativeLengthSVGRootsInvalidation(false)
#endif
{
}

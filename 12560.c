void DocumentLoader::stopLoadingSubresources()
{
    cancelAll(m_subresourceLoaders);
}

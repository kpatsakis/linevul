void DocumentLoader::removeSubresourceLoader(ResourceLoader* loader)
{
    if (!m_subresourceLoaders.contains(loader))
        return;
    m_subresourceLoaders.remove(loader);
    checkLoadComplete();
    if (Frame* frame = m_frame)
        frame->loader()->checkLoadComplete();
}

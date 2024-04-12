void DocumentLoader::commitLoad(const char* data, int length)
{
    RefPtr<Frame> protectFrame(m_frame);
    RefPtr<DocumentLoader> protectLoader(this);

    commitIfReady();
    FrameLoader* frameLoader = DocumentLoader::frameLoader();
    if (!frameLoader)
        return;
#if ENABLE(WEB_ARCHIVE) || ENABLE(MHTML)
    if (ArchiveFactory::isArchiveMimeType(response().mimeType()))
        return;
#endif
    frameLoader->client()->committedLoad(this, data, length);
}

void JPEGImageDecoder::decode(bool onlySize)
{
    if (failed())
        return;

    if (!m_reader)
        m_reader = adoptPtr(new JPEGImageReader(this));

    if (!m_reader->decode(*m_data, onlySize) && isAllDataReceived())
        setFailed();
    else if (!m_frameBufferCache.isEmpty() && (m_frameBufferCache[0].status() == ImageFrame::FrameComplete))
        m_reader.clear();
}

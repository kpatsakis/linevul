void ReadableStreamReader::releaseLock()
{
    if (!isActive())
        return;

    ASSERT(!m_stream->hasPendingReads());
    if (m_stream->stateInternal() != ReadableStream::Readable)
        m_closed->reset();
    m_closed->reject(DOMException::create(AbortError, "the reader is already released"));

    m_stream->setReader(nullptr);
    ASSERT(!isActive());
}

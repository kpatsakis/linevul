void ReadableStream::closeInternal()
{
    ASSERT(m_state == Readable);
    m_state = Closed;
    resolveAllPendingReadsAsDone();
    clearQueue();
    if (m_reader)
        m_reader->close();
}

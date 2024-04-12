ReadableStream::ReadableStream(UnderlyingSource* source)
    : m_source(source)
    , m_isStarted(false)
    , m_isDraining(false)
    , m_isPulling(false)
    , m_isDisturbed(false)
    , m_state(Readable)
{
}

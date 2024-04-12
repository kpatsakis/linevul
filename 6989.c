void Document::explicitClose()
{
    if (RefPtr<DocumentParser> parser = m_parser)
        parser->finish();

    if (!m_frame) {
        implicitClose();
        return;
    }

    m_frame->loader()->checkCompleted();
}

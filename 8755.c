void XMLHttpRequest::abort()
{
    RefPtr<XMLHttpRequest> protect(this);

    bool sendFlag = m_loader;

    internalAbort();

    clearResponseBuffers();

    m_requestHeaders.clear();

    if ((m_state <= OPENED && !sendFlag) || m_state == DONE)
        m_state = UNSENT;
    else {
        ASSERT(!m_loader);
        changeState(DONE);
        m_state = UNSENT;
    }

    m_progressEventThrottle.dispatchEventAndLoadEnd(XMLHttpRequestProgressEvent::create(eventNames().abortEvent));
    if (!m_uploadComplete) {
        m_uploadComplete = true;
        if (m_upload && m_uploadEventsAllowed)
            m_upload->dispatchEventAndLoadEnd(XMLHttpRequestProgressEvent::create(eventNames().abortEvent));
    }
}

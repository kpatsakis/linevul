void XMLHttpRequest::didSendData(unsigned long long bytesSent, unsigned long long totalBytesToBeSent)
{
    if (!m_upload)
        return;

    if (m_uploadEventsAllowed)
        m_upload->dispatchEvent(XMLHttpRequestProgressEvent::create(eventNames().progressEvent, true, bytesSent, totalBytesToBeSent));

    if (bytesSent == totalBytesToBeSent && !m_uploadComplete) {
        m_uploadComplete = true;
        if (m_uploadEventsAllowed)
            m_upload->dispatchEventAndLoadEnd(XMLHttpRequestProgressEvent::create(eventNames().loadEvent));
    }
}

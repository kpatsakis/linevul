void XMLHttpRequest::clearResponseBuffers()
{
    m_responseText.clear();
    m_responseEncoding = String();
    m_createdDocument = false;
    m_responseDocument = 0;
    m_responseBlob = 0;
    m_responseStream = 0;
    m_binaryResponseBuilder.clear();
    m_responseArrayBuffer.clear();
}

void WebPagePrivate::onInputLocaleChanged(bool isRTL)
{
    if (isRTL != m_webSettings->isWritingDirectionRTL()) {
        m_webSettings->setWritingDirectionRTL(isRTL);
        m_inputHandler->handleInputLocaleChanged(isRTL);
    }
}

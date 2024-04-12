 bool RTCPeerConnectionHandlerChromium::updateIce(PassRefPtr<RTCConfiguration> configuration, PassRefPtr<MediaConstraints> constraints)
 {
     if (!m_webHandler)
        return false;

    return m_webHandler->updateICE(configuration, constraints);
}

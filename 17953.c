void RTCPeerConnection::close(ExceptionCode& ec)
{
    if (m_readyState == ReadyStateClosing || m_readyState == ReadyStateClosed) {
        ec = INVALID_STATE_ERR;
        return;
    }

    changeIceState(IceStateClosed);
    changeReadyState(ReadyStateClosed);
    stop();
}

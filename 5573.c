void RilSapSocket::onCommandsSocketClosed() {
    sendDisconnect();
    RLOGE("Socket command closed");
}

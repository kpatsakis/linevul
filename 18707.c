status_t MediaPlayerService::Client::setRetransmitEndpoint(
 const struct sockaddr_in* endpoint) {

 if (NULL != endpoint) {
 uint32_t a = ntohl(endpoint->sin_addr.s_addr);
 uint16_t p = ntohs(endpoint->sin_port);
        ALOGV("[%d] setRetransmitEndpoint(%u.%u.%u.%u:%hu)", mConnId,
 (a >> 24), (a >> 16) & 0xFF, (a >> 8) & 0xFF, (a & 0xFF), p);
 } else {
        ALOGV("[%d] setRetransmitEndpoint = <none>", mConnId);
 }

    sp<MediaPlayerBase> p = getPlayer();

 if (p != 0) return INVALID_OPERATION;

 if (NULL != endpoint) {
        mRetransmitEndpoint = *endpoint;
        mRetransmitEndpointValid = true;
 } else {
        mRetransmitEndpointValid = false;
 }

 return NO_ERROR;
}

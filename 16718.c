status_t MediaPlayer::setRetransmitEndpoint(const char* addrString,
 uint16_t port) {
    ALOGV("MediaPlayer::setRetransmitEndpoint(%s:%hu)",
            addrString ? addrString : "(null)", port);

 Mutex::Autolock _l(mLock);
 if ((mPlayer != NULL) || (mCurrentState != MEDIA_PLAYER_IDLE))
 return INVALID_OPERATION;

 if (NULL == addrString) {
        mRetransmitEndpointValid = false;
 return OK;
 }

 struct in_addr saddr;
 if(!inet_aton(addrString, &saddr)) {
 return BAD_VALUE;
 }

    memset(&mRetransmitEndpoint, 0, sizeof(mRetransmitEndpoint));
    mRetransmitEndpoint.sin_family = AF_INET;
    mRetransmitEndpoint.sin_addr   = saddr;
    mRetransmitEndpoint.sin_port   = htons(port);
    mRetransmitEndpointValid       = true;

 return OK;
}

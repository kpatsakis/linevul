status_t MetadataRetrieverClient::setDataSource(
 const sp<IMediaHTTPService> &httpService,
 const char *url,
 const KeyedVector<String8, String8> *headers)
{
    ALOGV("setDataSource(%s)", url);
 Mutex::Autolock lock(mLock);
 if (url == NULL) {
 return UNKNOWN_ERROR;
 }

    player_type playerType =
 MediaPlayerFactory::getPlayerType(NULL /* client */, url);
    ALOGV("player type = %d", playerType);
    sp<MediaMetadataRetrieverBase> p = createRetriever(playerType);
 if (p == NULL) return NO_INIT;
 status_t ret = p->setDataSource(httpService, url, headers);
 if (ret == NO_ERROR) mRetriever = p;
 return ret;
}

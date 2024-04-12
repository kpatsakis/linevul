status_t NuMediaExtractor::setDataSource(
 const sp<IMediaHTTPService> &httpService,
 const char *path,
 const KeyedVector<String8, String8> *headers) {
 Mutex::Autolock autoLock(mLock);

 if (mImpl != NULL) {
 return -EINVAL;
 }

    sp<DataSource> dataSource =
 DataSource::CreateFromURI(httpService, path, headers);

 if (dataSource == NULL) {
 return -ENOENT;
 }

    mIsWidevineExtractor = false;
 if (!strncasecmp("widevine://", path, 11)) {
 String8 mimeType;
 float confidence;
        sp<AMessage> dummy;
 bool success = SniffWVM(dataSource, &mimeType, &confidence, &dummy);

 if (!success
 || strcasecmp(
                    mimeType.string(), MEDIA_MIMETYPE_CONTAINER_WVM)) {
 return ERROR_UNSUPPORTED;
 }

        sp<WVMExtractor> extractor = new WVMExtractor(dataSource);
        extractor->setAdaptiveStreamingMode(true);

        mImpl = extractor;
        mIsWidevineExtractor = true;
 } else {
        mImpl = MediaExtractor::Create(dataSource);
 }

 if (mImpl == NULL) {
 return ERROR_UNSUPPORTED;
 }

    sp<MetaData> fileMeta = mImpl->getMetaData();
 const char *containerMime;
 if (fileMeta != NULL
 && fileMeta->findCString(kKeyMIMEType, &containerMime)
 && !strcasecmp(containerMime, "video/wvm")) {
 static_cast<WVMExtractor *>(mImpl.get())->setCryptoPluginMode(true);
 } else if (mImpl->getDrmFlag()) {
        mImpl.clear();
        mImpl = NULL;
 return ERROR_UNSUPPORTED;
 }

 status_t err = updateDurationAndBitrate();
 if (err == OK) {
        mDataSource = dataSource;
 }

 return OK;
}

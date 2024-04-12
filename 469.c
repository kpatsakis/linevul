status_t NuMediaExtractor::setDataSource(int fd, off64_t offset, off64_t size) {

    ALOGV("setDataSource fd=%d (%s), offset=%lld, length=%lld",
            fd, nameForFd(fd).c_str(), (long long) offset, (long long) size);

 Mutex::Autolock autoLock(mLock);

 if (mImpl != NULL) {
 return -EINVAL;
 }

    sp<FileSource> fileSource = new FileSource(dup(fd), offset, size);

 status_t err = fileSource->initCheck();
 if (err != OK) {
 return err;
 }

    mImpl = MediaExtractor::Create(fileSource);

 if (mImpl == NULL) {
 return ERROR_UNSUPPORTED;
 }

    err = updateDurationAndBitrate();
 if (err == OK) {
        mDataSource = fileSource;
 }

 return OK;
}

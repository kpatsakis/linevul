status_t MPEG4Extractor::readMetaData() {
 if (mInitCheck != NO_INIT) {
 return mInitCheck;
 }

 off64_t offset = 0;
 status_t err;
 while (true) {
        err = parseChunk(&offset, 0);
 if (err == OK) {
 continue;
 }

 uint32_t hdr[2];
 if (mDataSource->readAt(offset, hdr, 8) < 8) {
 break;
 }
 uint32_t chunk_type = ntohl(hdr[1]);
 if (chunk_type == FOURCC('s', 'i', 'd', 'x')) {
 continue;
 } else if (chunk_type == FOURCC('m', 'o', 'o', 'f')) {
            mMoofOffset = offset;
 }
 break;
 }

 if (mInitCheck == OK) {
 if (mHasVideo) {
            mFileMetaData->setCString(
                    kKeyMIMEType, MEDIA_MIMETYPE_CONTAINER_MPEG4);
 } else {
            mFileMetaData->setCString(kKeyMIMEType, "audio/mp4");
 }

        mInitCheck = OK;
 } else {
        mInitCheck = err;
 }

    CHECK_NE(err, (status_t)NO_INIT);

 int psshsize = 0;
 for (size_t i = 0; i < mPssh.size(); i++) {
        psshsize += 20 + mPssh[i].datalen;
 }
 if (psshsize) {
 char *buf = (char*)malloc(psshsize);
 char *ptr = buf;
 for (size_t i = 0; i < mPssh.size(); i++) {
            memcpy(ptr, mPssh[i].uuid, 20); // uuid + length
            memcpy(ptr + 20, mPssh[i].data, mPssh[i].datalen);
            ptr += (20 + mPssh[i].datalen);
 }
        mFileMetaData->setData(kKeyPssh, 'pssh', buf, psshsize);
        free(buf);
 }
 return mInitCheck;
}

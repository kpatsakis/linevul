status_t MPEG4Extractor::readMetaData() {
 if (mInitCheck != NO_INIT) {
 return mInitCheck;
 }

 off64_t offset = 0;
 status_t err;
 while (true) {
 off64_t orig_offset = offset;
        err = parseChunk(&offset, 0);

 if (err != OK && err != UNKNOWN_ERROR) {
 break;
 } else if (offset <= orig_offset) {
            ALOGE("did not advance: 0x%lld->0x%lld", orig_offset, offset);
            err = ERROR_MALFORMED;
 break;
 } else if (err == OK) {
 continue;
 }

 uint32_t hdr[2];
 if (mDataSource->readAt(offset, hdr, 8) < 8) {
 break;
 }
 uint32_t chunk_type = ntohl(hdr[1]);
 if (chunk_type == FOURCC('m', 'o', 'o', 'f')) {
            mMoofOffset = offset;
 } else if (chunk_type != FOURCC('m', 'd', 'a', 't')) {
 continue;
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

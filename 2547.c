status_t MPEG4Extractor::parseTrackHeader(
 off64_t data_offset, off64_t data_size) {
 if (data_size < 4) {
 return ERROR_MALFORMED;
 }

 uint8_t version;
 if (mDataSource->readAt(data_offset, &version, 1) < 1) {
 return ERROR_IO;
 }

 size_t dynSize = (version == 1) ? 36 : 24;

 uint8_t buffer[36 + 60];

 if (data_size != (off64_t)dynSize + 60) {
 return ERROR_MALFORMED;
 }

 if (mDataSource->readAt(
                data_offset, buffer, data_size) < (ssize_t)data_size) {
 return ERROR_IO;
 }

 uint64_t ctime __unused, mtime __unused, duration __unused;
 int32_t id;

 if (version == 1) {
        ctime = U64_AT(&buffer[4]);
        mtime = U64_AT(&buffer[12]);
        id = U32_AT(&buffer[20]);
        duration = U64_AT(&buffer[28]);
 } else if (version == 0) {
        ctime = U32_AT(&buffer[4]);
        mtime = U32_AT(&buffer[8]);
        id = U32_AT(&buffer[12]);
        duration = U32_AT(&buffer[20]);
 } else {
 return ERROR_UNSUPPORTED;
 }

 if (mLastTrack == NULL)
 return ERROR_MALFORMED;

    mLastTrack->meta->setInt32(kKeyTrackID, id);

 size_t matrixOffset = dynSize + 16;
 int32_t a00 = U32_AT(&buffer[matrixOffset]);
 int32_t a01 = U32_AT(&buffer[matrixOffset + 4]);
 int32_t a10 = U32_AT(&buffer[matrixOffset + 12]);
 int32_t a11 = U32_AT(&buffer[matrixOffset + 16]);

#if 0
 int32_t dx = U32_AT(&buffer[matrixOffset + 8]);
 int32_t dy = U32_AT(&buffer[matrixOffset + 20]);

    ALOGI("x' = %.2f * x + %.2f * y + %.2f",
         a00 / 65536.0f, a01 / 65536.0f, dx / 65536.0f);
    ALOGI("y' = %.2f * x + %.2f * y + %.2f",
         a10 / 65536.0f, a11 / 65536.0f, dy / 65536.0f);
#endif

 uint32_t rotationDegrees;

 static const int32_t kFixedOne = 0x10000;
 if (a00 == kFixedOne && a01 == 0 && a10 == 0 && a11 == kFixedOne) {
        rotationDegrees = 0;
 } else if (a00 == 0 && a01 == kFixedOne && a10 == -kFixedOne && a11 == 0) {
        rotationDegrees = 90;
 } else if (a00 == 0 && a01 == -kFixedOne && a10 == kFixedOne && a11 == 0) {
        rotationDegrees = 270;
 } else if (a00 == -kFixedOne && a01 == 0 && a10 == 0 && a11 == -kFixedOne) {
        rotationDegrees = 180;
 } else {
        ALOGW("We only support 0,90,180,270 degree rotation matrices");
        rotationDegrees = 0;
 }

 if (rotationDegrees != 0) {
        mLastTrack->meta->setInt32(kKeyRotation, rotationDegrees);
 }

 uint32_t width = U32_AT(&buffer[dynSize + 52]);
 uint32_t height = U32_AT(&buffer[dynSize + 56]);
    mLastTrack->meta->setInt32(kKeyDisplayWidth, width >> 16);
    mLastTrack->meta->setInt32(kKeyDisplayHeight, height >> 16);

 return OK;
}

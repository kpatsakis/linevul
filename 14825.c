bool SniffOgg(
 const sp<DataSource> &source, String8 *mimeType, float *confidence,
        sp<AMessage> *) {
 char tmp[4];
 if (source->readAt(0, tmp, 4) < 4 || memcmp(tmp, "OggS", 4)) {
 return false;
 }

    mimeType->setTo(MEDIA_MIMETYPE_CONTAINER_OGG);
 *confidence = 0.2f;

 return true;
}

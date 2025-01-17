status_t OMXNodeInstance::emptyBuffer(
        OMX::buffer_id buffer,
        OMX_U32 rangeOffset, OMX_U32 rangeLength,
        OMX_U32 flags, OMX_TICKS timestamp, int fenceFd) {
 Mutex::Autolock autoLock(mLock);

 if (getGraphicBufferSource() != NULL) {
        android_errorWriteLog(0x534e4554, "29422020");
 return INVALID_OPERATION;
 }

    OMX_BUFFERHEADERTYPE *header = findBufferHeader(buffer, kPortIndexInput);
 if (header == NULL) {
        ALOGE("b/25884056");
 return BAD_VALUE;
 }
 BufferMeta *buffer_meta =
 static_cast<BufferMeta *>(header->pAppPrivate);

 if (mMetadataType[kPortIndexInput] == kMetadataBufferTypeGrallocSource) {
        header->nFilledLen = rangeLength ? sizeof(VideoGrallocMetadata) : 0;
        header->nOffset = 0;
 } else {
 if (rangeOffset > header->nAllocLen
 || rangeLength > header->nAllocLen - rangeOffset) {
            CLOG_ERROR(emptyBuffer, OMX_ErrorBadParameter, FULL_BUFFER(NULL, header, fenceFd));
 if (fenceFd >= 0) {
 ::close(fenceFd);
 }
 return BAD_VALUE;
 }
        header->nFilledLen = rangeLength;
        header->nOffset = rangeOffset;

        buffer_meta->CopyToOMX(header);
 }

 return emptyBuffer_l(header, flags, timestamp, (intptr_t)buffer, fenceFd);
}

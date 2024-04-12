void OMXNodeInstance::onMessage(const omx_message &msg) {
 const sp<GraphicBufferSource>& bufferSource(getGraphicBufferSource());

 if (msg.type == omx_message::FILL_BUFFER_DONE) {
        OMX_BUFFERHEADERTYPE *buffer =
            findBufferHeader(msg.u.extended_buffer_data.buffer);

 {
 Mutex::Autolock _l(mDebugLock);
            mOutputBuffersWithCodec.remove(buffer);

            CLOG_BUMPED_BUFFER(
                    FBD, WITH_STATS(FULL_BUFFER(msg.u.extended_buffer_data.buffer, buffer)));

            unbumpDebugLevel_l(kPortIndexOutput);
 }

 BufferMeta *buffer_meta =
 static_cast<BufferMeta *>(buffer->pAppPrivate);

        buffer_meta->CopyFromOMX(buffer);

 if (bufferSource != NULL) {
            bufferSource->codecBufferFilled(buffer);

            omx_message newMsg = msg;
            newMsg.u.extended_buffer_data.timestamp = buffer->nTimeStamp;
            mObserver->onMessage(newMsg);
 return;
 }
 } else if (msg.type == omx_message::EMPTY_BUFFER_DONE) {
        OMX_BUFFERHEADERTYPE *buffer =
            findBufferHeader(msg.u.buffer_data.buffer);

 {
 Mutex::Autolock _l(mDebugLock);
            mInputBuffersWithCodec.remove(buffer);

            CLOG_BUMPED_BUFFER(
                    EBD, WITH_STATS(EMPTY_BUFFER(msg.u.buffer_data.buffer, buffer)));
 }

 if (bufferSource != NULL) {
            bufferSource->codecBufferEmptied(buffer);
 return;
 }
 }

    mObserver->onMessage(msg);
}

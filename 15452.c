void OMXCodec::on_message(const omx_message &msg) {
 if (mState == ERROR) {
 /*
         * only drop EVENT messages, EBD and FBD are still
         * processed for bookkeeping purposes
         */
 if (msg.type == omx_message::EVENT) {
            ALOGW("Dropping OMX EVENT message - we're in ERROR state.");
 return;
 }
 }

 switch (msg.type) {
 case omx_message::EVENT:
 {
            onEvent(
                 msg.u.event_data.event, msg.u.event_data.data1,
                 msg.u.event_data.data2);

 break;
 }

 case omx_message::EMPTY_BUFFER_DONE:
 {
            IOMX::buffer_id buffer = msg.u.extended_buffer_data.buffer;

            CODEC_LOGV("EMPTY_BUFFER_DONE(buffer: %u)", buffer);

 Vector<BufferInfo> *buffers = &mPortBuffers[kPortIndexInput];
 size_t i = 0;
 while (i < buffers->size() && (*buffers)[i].mBuffer != buffer) {
 ++i;
 }

            CHECK(i < buffers->size());
 if ((*buffers)[i].mStatus != OWNED_BY_COMPONENT) {
                ALOGW("We already own input buffer %u, yet received "
 "an EMPTY_BUFFER_DONE.", buffer);
 }

 BufferInfo* info = &buffers->editItemAt(i);
            info->mStatus = OWNED_BY_US;

 if (info->mMediaBuffer != NULL) {
                info->mMediaBuffer->release();
                info->mMediaBuffer = NULL;
 }

 if (mPortStatus[kPortIndexInput] == DISABLING) {
                CODEC_LOGV("Port is disabled, freeing buffer %u", buffer);

 status_t err = freeBuffer(kPortIndexInput, i);
                CHECK_EQ(err, (status_t)OK);
 } else if (mState != ERROR
 && mPortStatus[kPortIndexInput] != SHUTTING_DOWN) {
                CHECK_EQ((int)mPortStatus[kPortIndexInput], (int)ENABLED);

 if (mFlags & kUseSecureInputBuffers) {
                    drainAnyInputBuffer();
 } else {
                    drainInputBuffer(&buffers->editItemAt(i));
 }
 }
 break;
 }

 case omx_message::FILL_BUFFER_DONE:
 {
            IOMX::buffer_id buffer = msg.u.extended_buffer_data.buffer;
            OMX_U32 flags = msg.u.extended_buffer_data.flags;

            CODEC_LOGV("FILL_BUFFER_DONE(buffer: %u, size: %u, flags: 0x%08x, timestamp: %lld us (%.2f secs))",
                 buffer,
                 msg.u.extended_buffer_data.range_length,
                 flags,
                 msg.u.extended_buffer_data.timestamp,
                 msg.u.extended_buffer_data.timestamp / 1E6);

 Vector<BufferInfo> *buffers = &mPortBuffers[kPortIndexOutput];
 size_t i = 0;
 while (i < buffers->size() && (*buffers)[i].mBuffer != buffer) {
 ++i;
 }

            CHECK(i < buffers->size());
 BufferInfo *info = &buffers->editItemAt(i);

 if (info->mStatus != OWNED_BY_COMPONENT) {
                ALOGW("We already own output buffer %u, yet received "
 "a FILL_BUFFER_DONE.", buffer);
 }

            info->mStatus = OWNED_BY_US;

 if (mPortStatus[kPortIndexOutput] == DISABLING) {
                CODEC_LOGV("Port is disabled, freeing buffer %u", buffer);

 status_t err = freeBuffer(kPortIndexOutput, i);
                CHECK_EQ(err, (status_t)OK);

#if 0
 } else if (mPortStatus[kPortIndexOutput] == ENABLED
 && (flags & OMX_BUFFERFLAG_EOS)) {
                CODEC_LOGV("No more output data.");
                mNoMoreOutputData = true;
                mBufferFilled.signal();
#endif
 } else if (mPortStatus[kPortIndexOutput] != SHUTTING_DOWN) {
                CHECK_EQ((int)mPortStatus[kPortIndexOutput], (int)ENABLED);

 MediaBuffer *buffer = info->mMediaBuffer;
 bool isGraphicBuffer = buffer->graphicBuffer() != NULL;

 if (!isGraphicBuffer
 && msg.u.extended_buffer_data.range_offset
 + msg.u.extended_buffer_data.range_length
 > buffer->size()) {
                    CODEC_LOGE(
 "Codec lied about its buffer size requirements, "
 "sending a buffer larger than the originally "
 "advertised size in FILL_BUFFER_DONE!");
 }
                buffer->set_range(
                        msg.u.extended_buffer_data.range_offset,
                        msg.u.extended_buffer_data.range_length);

                buffer->meta_data()->clear();

                buffer->meta_data()->setInt64(
                        kKeyTime, msg.u.extended_buffer_data.timestamp);

 if (msg.u.extended_buffer_data.flags & OMX_BUFFERFLAG_SYNCFRAME) {
                    buffer->meta_data()->setInt32(kKeyIsSyncFrame, true);
 }
 bool isCodecSpecific = false;
 if (msg.u.extended_buffer_data.flags & OMX_BUFFERFLAG_CODECCONFIG) {
                    buffer->meta_data()->setInt32(kKeyIsCodecConfig, true);
                    isCodecSpecific = true;
 }

 if (isGraphicBuffer || mQuirks & kOutputBuffersAreUnreadable) {
                    buffer->meta_data()->setInt32(kKeyIsUnreadable, true);
 }

                buffer->meta_data()->setInt32(
                        kKeyBufferID,
                        msg.u.extended_buffer_data.buffer);

 if (msg.u.extended_buffer_data.flags & OMX_BUFFERFLAG_EOS) {
                    CODEC_LOGV("No more output data.");
                    mNoMoreOutputData = true;
 }

 if (mIsEncoder && mIsVideo) {
 int64_t decodingTimeUs = isCodecSpecific? 0: getDecodingTimeUs();
                    buffer->meta_data()->setInt64(kKeyDecodingTime, decodingTimeUs);
 }

 if (mTargetTimeUs >= 0) {
                    CHECK(msg.u.extended_buffer_data.timestamp <= mTargetTimeUs);

 if (msg.u.extended_buffer_data.timestamp < mTargetTimeUs) {
                        CODEC_LOGV(
 "skipping output buffer at timestamp %lld us",
                                msg.u.extended_buffer_data.timestamp);

                        fillOutputBuffer(info);
 break;
 }

                    CODEC_LOGV(
 "returning output buffer at target timestamp "
 "%lld us",
                            msg.u.extended_buffer_data.timestamp);

                    mTargetTimeUs = -1;
 }

                mFilledBuffers.push_back(i);
                mBufferFilled.signal();
 if (mIsEncoder) {
                    sched_yield();
 }
 }

 break;
 }

 default:
 {
            CHECK(!"should not be here.");
 break;
 }
 }
}

void SimpleSoftOMXComponent::onMessageReceived(const sp<AMessage> &msg) {
 Mutex::Autolock autoLock(mLock);
 uint32_t msgType = msg->what();
    ALOGV("msgType = %d", msgType);
 switch (msgType) {
 case kWhatSendCommand:
 {
 int32_t cmd, param;
            CHECK(msg->findInt32("cmd", &cmd));
            CHECK(msg->findInt32("param", &param));

            onSendCommand((OMX_COMMANDTYPE)cmd, (OMX_U32)param);
 break;
 }

 case kWhatEmptyThisBuffer:
 case kWhatFillThisBuffer:
 {
            OMX_BUFFERHEADERTYPE *header;
            CHECK(msg->findPointer("header", (void **)&header));

            CHECK(mState == OMX_StateExecuting && mTargetState == mState);

 bool found = false;
 size_t portIndex = (kWhatEmptyThisBuffer == msgType)?
                    header->nInputPortIndex: header->nOutputPortIndex;
 PortInfo *port = &mPorts.editItemAt(portIndex);

 for (size_t j = 0; j < port->mBuffers.size(); ++j) {
 BufferInfo *buffer = &port->mBuffers.editItemAt(j);

 if (buffer->mHeader == header) {
                    CHECK(!buffer->mOwnedByUs);

                    buffer->mOwnedByUs = true;

                    CHECK((msgType == kWhatEmptyThisBuffer
 && port->mDef.eDir == OMX_DirInput)
 || (port->mDef.eDir == OMX_DirOutput));

                    port->mQueue.push_back(buffer);
                    onQueueFilled(portIndex);

                    found = true;
 break;
 }
 }

            CHECK(found);
 break;
 }

 default:
            TRESPASS();
 break;
 }
}

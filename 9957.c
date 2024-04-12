OMX_BUFFERHEADERTYPE *OMXNodeInstance::findBufferHeader(OMX::buffer_id buffer) {
 if (buffer == 0) {
 return NULL;
 }
 Mutex::Autolock autoLock(mBufferIDLock);
 return mBufferIDToBufferHeader.valueFor(buffer);
}

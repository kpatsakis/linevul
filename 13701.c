 virtual status_t acquireBuffer(BufferItem *buffer, nsecs_t presentWhen,
 uint64_t maxFrameNumber) {
 Parcel data, reply;
        data.writeInterfaceToken(IGraphicBufferConsumer::getInterfaceDescriptor());
        data.writeInt64(presentWhen);
        data.writeUint64(maxFrameNumber);
 status_t result = remote()->transact(ACQUIRE_BUFFER, data, &reply);
 if (result != NO_ERROR) {
 return result;
 }
        result = reply.read(*buffer);
 if (result != NO_ERROR) {
 return result;
 }
 return reply.readInt32();
 }

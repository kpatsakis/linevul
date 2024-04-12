 virtual void allocateBuffers(bool async, uint32_t width, uint32_t height,
 PixelFormat format, uint32_t usage) {
 Parcel data, reply;
        data.writeInterfaceToken(IGraphicBufferProducer::getInterfaceDescriptor());
        data.writeInt32(static_cast<int32_t>(async));
        data.writeUint32(width);
        data.writeUint32(height);
        data.writeInt32(static_cast<int32_t>(format));
        data.writeUint32(usage);
 status_t result = remote()->transact(ALLOCATE_BUFFERS, data, &reply);
 if (result != NO_ERROR) {
            ALOGE("allocateBuffers failed to transact: %d", result);
 }
 }

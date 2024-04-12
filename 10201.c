 virtual status_t setDefaultBufferDataSpace(
            android_dataspace defaultDataSpace) {
 Parcel data, reply;
        data.writeInterfaceToken(IGraphicBufferConsumer::getInterfaceDescriptor());
        data.writeInt32(static_cast<int32_t>(defaultDataSpace));
 status_t result = remote()->transact(SET_DEFAULT_BUFFER_DATA_SPACE,
                data, &reply);
 if (result != NO_ERROR) {
 return result;
 }
 return reply.readInt32();
 }

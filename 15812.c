 virtual status_t setConsumerUsageBits(uint32_t usage) {
 Parcel data, reply;
        data.writeInterfaceToken(IGraphicBufferConsumer::getInterfaceDescriptor());
        data.writeInt32(usage);
 status_t result = remote()->transact(SET_CONSUMER_USAGE_BITS, data, &reply);
 if (result != NO_ERROR) {
 return result;
 }
 return reply.readInt32();
 }

 virtual void unsetHeap(int32_t seqNum) {
 Parcel data, reply;
        data.writeInterfaceToken(ICrypto::getInterfaceDescriptor());
        data.writeInt32(seqNum);
        remote()->transact(UNSET_HEAP, data, &reply);
 return;
 }

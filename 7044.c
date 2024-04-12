 virtual status_t getState(
            node_id node, OMX_STATETYPE* state) {
 Parcel data, reply;
        data.writeInterfaceToken(IOMX::getInterfaceDescriptor());
        data.writeInt32((int32_t)node);
        remote()->transact(GET_STATE, data, &reply);

 *state = static_cast<OMX_STATETYPE>(reply.readInt32());
 return reply.readInt32();
 }

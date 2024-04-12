 virtual status_t getParameter(
            node_id node, OMX_INDEXTYPE index,
 void *params, size_t size) {
 Parcel data, reply;
        data.writeInterfaceToken(IOMX::getInterfaceDescriptor());
        data.writeInt32((int32_t)node);
        data.writeInt32(index);
        data.writeInt64(size);
        data.write(params, size);
        remote()->transact(GET_PARAMETER, data, &reply);

 status_t err = reply.readInt32();
 if (err != OK) {
 return err;
 }

        reply.read(params, size);

 return OK;
 }

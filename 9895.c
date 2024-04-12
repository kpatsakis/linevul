 virtual status_t closeSession(Vector<uint8_t> const &sessionId) {
 Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
 status_t status = remote()->transact(CLOSE_SESSION, data, &reply);
 if (status != OK) {
 return status;
 }

 return reply.readInt32();
 }

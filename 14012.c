 virtual status_t signRSA(Vector<uint8_t> const &sessionId,
 String8 const &algorithm,
 Vector<uint8_t> const &message,
 Vector<uint8_t> const &wrappedKey,
 Vector<uint8_t> &signature) {
 Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
        data.writeString8(algorithm);
        writeVector(data, message);
        writeVector(data, wrappedKey);

 status_t status = remote()->transact(SIGN_RSA, data, &reply);
 if (status != OK) {
 return status;
 }
        readVector(reply, signature);

 return reply.readInt32();
 }

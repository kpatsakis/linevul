status_t IPCThreadState::sendReply(const Parcel& reply, uint32_t flags)
{
 status_t err;
 status_t statusBuffer;
    err = writeTransactionData(BC_REPLY, flags, -1, 0, reply, &statusBuffer);
 if (err < NO_ERROR) return err;
 
 return waitForResponse(NULL, NULL);
}

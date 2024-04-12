status_t IPCThreadState::waitForResponse(Parcel *reply, status_t *acquireResult)
{
 uint32_t cmd;
 int32_t err;

 while (1) {
 if ((err=talkWithDriver()) < NO_ERROR) break;
        err = mIn.errorCheck();
 if (err < NO_ERROR) break;
 if (mIn.dataAvail() == 0) continue;
 
        cmd = (uint32_t)mIn.readInt32();
 
        IF_LOG_COMMANDS() {
            alog << "Processing waitForResponse Command: "
 << getReturnString(cmd) << endl;
 }

 switch (cmd) {
 case BR_TRANSACTION_COMPLETE:
 if (!reply && !acquireResult) goto finish;
 break;
 
 case BR_DEAD_REPLY:
            err = DEAD_OBJECT;
 goto finish;

 case BR_FAILED_REPLY:
            err = FAILED_TRANSACTION;
 goto finish;
 
 case BR_ACQUIRE_RESULT:
 {
                ALOG_ASSERT(acquireResult != NULL, "Unexpected brACQUIRE_RESULT");
 const int32_t result = mIn.readInt32();
 if (!acquireResult) continue;
 *acquireResult = result ? NO_ERROR : INVALID_OPERATION;
 }
 goto finish;
 
 case BR_REPLY:
 {
                binder_transaction_data tr;
                err = mIn.read(&tr, sizeof(tr));
                ALOG_ASSERT(err == NO_ERROR, "Not enough command data for brREPLY");
 if (err != NO_ERROR) goto finish;

 if (reply) {
 if ((tr.flags & TF_STATUS_CODE) == 0) {
                        reply->ipcSetDataReference(
 reinterpret_cast<const uint8_t*>(tr.data.ptr.buffer),
                            tr.data_size,
 reinterpret_cast<const binder_size_t*>(tr.data.ptr.offsets),
                            tr.offsets_size/sizeof(binder_size_t),
                            freeBuffer, this);
 } else {
                        err = *reinterpret_cast<const status_t*>(tr.data.ptr.buffer);
                        freeBuffer(NULL,
 reinterpret_cast<const uint8_t*>(tr.data.ptr.buffer),
                            tr.data_size,
 reinterpret_cast<const binder_size_t*>(tr.data.ptr.offsets),
                            tr.offsets_size/sizeof(binder_size_t), this);
 }
 } else {
                    freeBuffer(NULL,
 reinterpret_cast<const uint8_t*>(tr.data.ptr.buffer),
                        tr.data_size,
 reinterpret_cast<const binder_size_t*>(tr.data.ptr.offsets),
                        tr.offsets_size/sizeof(binder_size_t), this);
 continue;
 }
 }
 goto finish;

 default:
            err = executeCommand(cmd);
 if (err != NO_ERROR) goto finish;
 break;
 }
 }

finish:
 if (err != NO_ERROR) {
 if (acquireResult) *acquireResult = err;
 if (reply) reply->setError(err);
        mLastError = err;
 }
 
 return err;
}

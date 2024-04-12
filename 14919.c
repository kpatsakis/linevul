dispatchCdmaSmsAck(Parcel &p, RequestInfo *pRI) {
    RIL_CDMA_SMS_Ack rcsa;
 int32_t  t;
 status_t status;
 int32_t digitCount;

    RLOGD("dispatchCdmaSmsAck");
    memset(&rcsa, 0, sizeof(rcsa));

    status = p.readInt32(&t);
    rcsa.uErrorClass = (RIL_CDMA_SMS_ErrorClass) t;

    status = p.readInt32(&t);
    rcsa.uSMSCauseCode = (int) t;

 if (status != NO_ERROR) {
 goto invalid;
 }

    startRequest;
    appendPrintBuf("%suErrorClass=%d, uTLStatus=%d, ",
            printBuf, rcsa.uErrorClass, rcsa.uSMSCauseCode);
    closeRequest;

    printRequest(pRI->token, pRI->pCI->requestNumber);

    CALL_ONREQUEST(pRI->pCI->requestNumber, &rcsa, sizeof(rcsa),pRI, pRI->socket_id);

#ifdef MEMSET_FREED
    memset(&rcsa, 0, sizeof(rcsa));
#endif

 return;

invalid:
    invalidCommandBlock(pRI);
 return;
}

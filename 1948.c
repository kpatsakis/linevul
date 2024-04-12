dispatchSIM_APDU (Parcel &p, RequestInfo *pRI) {
 int32_t t;
 status_t status;
    RIL_SIM_APDU apdu;

#if VDBG
    RLOGD("dispatchSIM_APDU");
#endif
    memset (&apdu, 0, sizeof(RIL_SIM_APDU));

    status = p.readInt32(&t);
    apdu.sessionid = (int)t;

    status = p.readInt32(&t);
    apdu.cla = (int)t;

    status = p.readInt32(&t);
    apdu.instruction = (int)t;

    status = p.readInt32(&t);
    apdu.p1 = (int)t;

    status = p.readInt32(&t);
    apdu.p2 = (int)t;

    status = p.readInt32(&t);
    apdu.p3 = (int)t;

    apdu.data = strdupReadString(p);

    startRequest;
    appendPrintBuf("%ssessionid=%d,cla=%d,ins=%d,p1=%d,p2=%d,p3=%d,data=%s",
        printBuf, apdu.sessionid, apdu.cla, apdu.instruction, apdu.p1, apdu.p2,
        apdu.p3, (char*)apdu.data);
    closeRequest;
    printRequest(pRI->token, pRI->pCI->requestNumber);

 if (status != NO_ERROR) {
 goto invalid;
 }

    CALL_ONREQUEST(pRI->pCI->requestNumber, &apdu, sizeof(RIL_SIM_APDU), pRI, pRI->socket_id);

#ifdef MEMSET_FREED
    memsetString(apdu.data);
#endif
    free(apdu.data);

#ifdef MEMSET_FREED
    memset(&apdu, 0, sizeof(RIL_SIM_APDU));
#endif

 return;
invalid:
    invalidCommandBlock(pRI);
 return;
}

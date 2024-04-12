static void dispatchSimAuthentication(Parcel &p, RequestInfo *pRI)
{
    RIL_SimAuthentication pf;
 int32_t  t;
 status_t status;

    memset(&pf, 0, sizeof(pf));

    status = p.readInt32(&t);
    pf.authContext = (int) t;
    pf.authData = strdupReadString(p);
    pf.aid = strdupReadString(p);

    startRequest;
    appendPrintBuf("authContext=%s, authData=%s, aid=%s", pf.authContext, pf.authData, pf.aid);
    closeRequest;
    printRequest(pRI->token, pRI->pCI->requestNumber);

 if (status != NO_ERROR) {
 goto invalid;
 }
    CALL_ONREQUEST(pRI->pCI->requestNumber, &pf, sizeof(pf), pRI, pRI->socket_id);

#ifdef MEMSET_FREED
    memsetString(pf.authData);
    memsetString(pf.aid);
#endif

    free(pf.authData);
    free(pf.aid);

#ifdef MEMSET_FREED
    memset(&pf, 0, sizeof(pf));
#endif

 return;
invalid:
    invalidCommandBlock(pRI);
 return;
}

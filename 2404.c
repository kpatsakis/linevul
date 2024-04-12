void RIL_onUnsolicitedResponse(int unsolResponse, const void *data,
 size_t datalen, RIL_SOCKET_ID socket_id)
#else
extern "C"
void RIL_onUnsolicitedResponse(int unsolResponse, const void *data,
 size_t datalen)
#endif
{
 int unsolResponseIndex;
 int ret;
 int64_t timeReceived = 0;
 bool shouldScheduleTimeout = false;
    RIL_RadioState newState;
    RIL_SOCKET_ID soc_id = RIL_SOCKET_1;

#if defined(ANDROID_MULTI_SIM)
    soc_id = socket_id;
#endif


 if (s_registerCalled == 0) {
        RLOGW("RIL_onUnsolicitedResponse called before RIL_register");
 return;
 }

    unsolResponseIndex = unsolResponse - RIL_UNSOL_RESPONSE_BASE;

 if ((unsolResponseIndex < 0)
 || (unsolResponseIndex >= (int32_t)NUM_ELEMS(s_unsolResponses))) {
        RLOGE("unsupported unsolicited response code %d", unsolResponse);
 return;
 }

 switch (s_unsolResponses[unsolResponseIndex].wakeType) {
 case WAKE_PARTIAL:
            grabPartialWakeLock();
            shouldScheduleTimeout = true;
 break;

 case DONT_WAKE:
 default:
            shouldScheduleTimeout = false;
 break;
 }

 if (unsolResponse == RIL_UNSOL_NITZ_TIME_RECEIVED) {
        timeReceived = elapsedRealtime();
 }

    appendPrintBuf("[UNSL]< %s", requestToString(unsolResponse));

 Parcel p;
 if (s_callbacks.version >= 13
 && s_unsolResponses[unsolResponseIndex].wakeType == WAKE_PARTIAL) {
        p.writeInt32 (RESPONSE_UNSOLICITED_ACK_EXP);
 } else {
        p.writeInt32 (RESPONSE_UNSOLICITED);
 }
    p.writeInt32 (unsolResponse);

    ret = s_unsolResponses[unsolResponseIndex]
 .responseFunction(p, const_cast<void*>(data), datalen);
 if (ret != 0) {
 goto error_exit;
 }

 switch(unsolResponse) {
 case RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED:
            newState = processRadioState(CALL_ONSTATEREQUEST(soc_id), soc_id);
            p.writeInt32(newState);
            appendPrintBuf("%s {%s}", printBuf,
                radioStateToString(CALL_ONSTATEREQUEST(soc_id)));
 break;


 case RIL_UNSOL_NITZ_TIME_RECEIVED:
            p.writeInt64(timeReceived);
 break;
 }

 if (s_callbacks.version < 13) {
 if (shouldScheduleTimeout) {
 UserCallbackInfo *p_info = internalRequestTimedCallback(wakeTimeoutCallback, NULL,
 &TIMEVAL_WAKE_TIMEOUT);

 if (p_info == NULL) {
 goto error_exit;
 } else {
 if (s_last_wake_timeout_info != NULL) {
                    s_last_wake_timeout_info->userParam = (void *)1;
 }
                s_last_wake_timeout_info = p_info;
 }
 }
 }

#if VDBG
    RLOGI("%s UNSOLICITED: %s length:%d", rilSocketIdToString(soc_id), requestToString(unsolResponse), p.dataSize());
#endif
    ret = sendResponse(p, soc_id);
 if (ret != 0 && unsolResponse == RIL_UNSOL_NITZ_TIME_RECEIVED) {


 if (s_lastNITZTimeData != NULL) {
            free (s_lastNITZTimeData);
            s_lastNITZTimeData = NULL;
 }

        s_lastNITZTimeData = calloc(p.dataSize(), 1);
 if (s_lastNITZTimeData == NULL) {
             RLOGE("Memory allocation failed in RIL_onUnsolicitedResponse");
 goto error_exit;
 }
        s_lastNITZTimeDataSize = p.dataSize();
        memcpy(s_lastNITZTimeData, p.data(), p.dataSize());
 }

 return;

error_exit:
 if (shouldScheduleTimeout) {
        releaseWakeLock();
 }
}

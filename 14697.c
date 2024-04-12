PassRefPtr<RTCVoidRequestImpl> RTCVoidRequestImpl::create(ScriptExecutionContext* context, PassRefPtr<VoidCallback> successCallback, PassRefPtr<RTCErrorCallback> errorCallback)
{
    RefPtr<RTCVoidRequestImpl> request = adoptRef(new RTCVoidRequestImpl(context, successCallback, errorCallback));
    request->suspendIfNeeded();
    return request.release();
}

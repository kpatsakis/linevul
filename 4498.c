BaseSessionService::Handle BaseSessionService::ScheduleGetLastSessionCommands(
    InternalGetCommandsRequest* request,
    CancelableRequestConsumerBase* consumer) {
  scoped_refptr<InternalGetCommandsRequest> request_wrapper(request);
  AddRequest(request, consumer);
  RunTaskOnBackendThread(
      FROM_HERE,
      base::Bind(&SessionBackend::ReadLastSessionCommands, backend(),
                 request_wrapper));
  return request->handle();
}

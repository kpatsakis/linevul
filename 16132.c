void CoordinatorImpl::OnOSMemoryDumpResponse(uint64_t dump_guid,
                                             mojom::ClientProcess* client,
                                             bool success,
                                             OSMemDumpMap os_dumps) {
  using ResponseType = QueuedRequest::PendingResponse::Type;
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  QueuedRequest* request = GetCurrentRequest();
  if (request == nullptr || request->dump_guid != dump_guid) {
    return;
  }

  RemovePendingResponse(client, ResponseType::kOSDump);

  if (!clients_.count(client)) {
    VLOG(1) << "Received a memory dump response from an unregistered client";
    return;
  }

  request->responses[client].os_dumps = std::move(os_dumps);

  if (!success) {
    request->failed_memory_dump_count++;
    VLOG(1) << "RequestGlobalMemoryDump() FAIL: NACK from client process";
  }

  FinalizeGlobalMemoryDumpIfAllManagersReplied();
}

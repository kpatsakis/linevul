void AudioRendererHost::OnNotifyPacketReady(
    const IPC::Message& msg, int stream_id, uint32 packet_size) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO));

  AudioEntry* entry = LookupById(msg.routing_id(), stream_id);
  if (!entry) {
    SendErrorMessage(msg.routing_id(), stream_id);
    return;
  }

  DCHECK(!entry->controller->LowLatencyMode());
  CHECK(packet_size <= entry->shared_memory.created_size());

  if (!entry->pending_buffer_request) {
    NOTREACHED() << "Buffer received but no such pending request";
  }
  entry->pending_buffer_request = false;

  entry->controller->EnqueueData(
      reinterpret_cast<uint8*>(entry->shared_memory.memory()),
      packet_size);
}

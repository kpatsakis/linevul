void AudioRendererHost::OnStreamCreated(
    int stream_id,
    base::SharedMemory* shared_memory,
    base::CancelableSyncSocket* foreign_socket) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);

  if (!PeerHandle()) {
    DLOG(WARNING) << "Renderer process handle is invalid.";
    OnStreamError(stream_id);
    return;
  }

  if (!LookupById(stream_id)) {
    OnStreamError(stream_id);
    return;
  }

  base::SharedMemoryHandle foreign_memory_handle;
  base::SyncSocket::TransitDescriptor socket_descriptor;
  size_t shared_memory_size = shared_memory->requested_size();

  if (!(shared_memory->ShareToProcess(PeerHandle(), &foreign_memory_handle) &&
        foreign_socket->PrepareTransitDescriptor(PeerHandle(),
                                                 &socket_descriptor))) {
    OnStreamError(stream_id);
    return;
  }

  Send(new AudioMsg_NotifyStreamCreated(
      stream_id, foreign_memory_handle, socket_descriptor,
      base::checked_cast<uint32_t>(shared_memory_size)));
}

void UDPSocketWin::DidCompleteRead() {
  DWORD num_bytes, flags;
  BOOL ok = WSAGetOverlappedResult(socket_, &core_->read_overlapped_,
                                   &num_bytes, FALSE, &flags);
  WSAResetEvent(core_->read_overlapped_.hEvent);
  int result = ok ? num_bytes : MapSystemError(WSAGetLastError());
  if (recv_from_address_ && result >= 0) {
    if (!ReceiveAddressToIPEndpoint(recv_from_address_))
      result = ERR_ADDRESS_INVALID;
  }
  LogRead(result, core_->read_iobuffer_->data());
  core_->read_iobuffer_ = NULL;
  recv_from_address_ = NULL;
  DoReadCallback(result);
}

void ReadableStreamBytesConsumer::OnRejected() {
  DCHECK(is_reading_);
  DCHECK(!pending_buffer_);
  is_reading_ = false;
  if (state_ == PublicState::kClosed)
    return;
  DCHECK_EQ(state_, PublicState::kReadableOrWaiting);
  state_ = PublicState::kErrored;
  reader_.Clear();
  Client* client = client_;
  ClearClient();
  if (client)
    client->OnStateChange();
}

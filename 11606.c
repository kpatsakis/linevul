void MojoAudioOutputStream::OnStreamError(int stream_id) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  client_->OnError();
  OnError();
}

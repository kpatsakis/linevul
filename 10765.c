void MojoAudioInputIPC::CloseStream() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  delegate_ = nullptr;
  if (factory_client_binding_.is_bound())
    factory_client_binding_.Unbind();
  if (stream_client_binding_.is_bound())
    stream_client_binding_.Unbind();
  stream_.reset();
}

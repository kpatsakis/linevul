void MojoAudioOutputIPC::CloseStream() {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  stream_provider_.reset();
  stream_.reset();
  binding_.Close();
  delegate_ = nullptr;

  weak_factory_.InvalidateWeakPtrs();
}

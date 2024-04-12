void SpeechRecognitionManagerImpl::StartSession(int session_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  if (!SessionExists(session_id))
    return;

  if (primary_session_id_ != kSessionIDInvalid &&
      primary_session_id_ != session_id) {
    AbortSession(primary_session_id_);
  }

  primary_session_id_ = session_id;

  if (delegate_) {
    delegate_->CheckRecognitionIsAllowed(
        session_id,
        base::BindOnce(
            &SpeechRecognitionManagerImpl::RecognitionAllowedCallback,
            weak_factory_.GetWeakPtr(), session_id));
  }
}

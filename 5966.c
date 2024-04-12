void Job::SetCallback(const CompletionCallback& callback) {
  CheckIsOnOriginThread();
  DCHECK(callback_.is_null());
  (*params_->num_outstanding_callbacks)++;
  callback_ = callback;
}

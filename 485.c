const char* HttpBridge::GetResponseContent() const {
  DCHECK_EQ(MessageLoop::current(), created_on_loop_);
  base::AutoLock lock(fetch_state_lock_);
  DCHECK(fetch_state_.request_completed);
  return fetch_state_.response_content.data();
}

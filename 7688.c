void HttpBridge::SetUserAgent(const char* user_agent) {
  DCHECK_EQ(MessageLoop::current(), created_on_loop_);
  if (DCHECK_IS_ON()) {
    base::AutoLock lock(fetch_state_lock_);
    DCHECK(!fetch_state_.request_completed);
  }
  context_getter_for_request_->set_user_agent(user_agent);
}

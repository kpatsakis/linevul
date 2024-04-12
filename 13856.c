void AppCacheDispatcherHost::OnGetStatus(int host_id, IPC::Message* reply_msg) {
  if (pending_reply_msg_) {
    bad_message::ReceivedBadMessage(
        this, bad_message::ACDH_PENDING_REPLY_IN_GET_STATUS);
    delete reply_msg;
    return;
  }

  pending_reply_msg_.reset(reply_msg);
  if (appcache_service_.get()) {
    if (!backend_impl_.GetStatusWithCallback(
            host_id, get_status_callback_, reply_msg)) {
      bad_message::ReceivedBadMessage(this, bad_message::ACDH_GET_STATUS);
    }
    return;
  }

  GetStatusCallback(APPCACHE_STATUS_UNCACHED, reply_msg);
}

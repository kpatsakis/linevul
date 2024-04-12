void ResourceMessageFilter::SendDelayedReply(IPC::Message* reply_msg) {
  Send(reply_msg);
}

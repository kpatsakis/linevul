 NaClProcessHost::~NaClProcessHost() {
  int exit_code;
  process_->GetTerminationStatus(&exit_code);
  std::string message =
      base::StringPrintf("NaCl process exited with status %i (0x%x)",
                         exit_code, exit_code);
  if (exit_code == 0) {
    LOG(INFO) << message;
  } else {
    LOG(ERROR) << message;
  }

  for (size_t i = 0; i < internal_->sockets_for_renderer.size(); i++) {
    if (nacl::Close(internal_->sockets_for_renderer[i]) != 0) {
      NOTREACHED() << "nacl::Close() failed";
    }
  }
  for (size_t i = 0; i < internal_->sockets_for_sel_ldr.size(); i++) {
    if (nacl::Close(internal_->sockets_for_sel_ldr[i]) != 0) {
      NOTREACHED() << "nacl::Close() failed";
    }
  }

  if (reply_msg_) {
    reply_msg_->set_reply_error();
    chrome_render_message_filter_->Send(reply_msg_);
  }
#if defined(OS_WIN)
  if (process_launched_by_broker_) {
    NaClBrokerService::GetInstance()->OnLoaderDied();
  }
#endif
}

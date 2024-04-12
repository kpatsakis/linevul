ConnectionToClient::ConnectionToClient(base::MessageLoopProxy* message_loop,
                                       protocol::Session* session)
    : message_loop_(message_loop),
      handler_(NULL),
      host_stub_(NULL),
      input_stub_(NULL),
      session_(session),
      control_connected_(false),
      input_connected_(false),
      video_connected_(false) {
  DCHECK(message_loop_);
  session_->SetStateChangeCallback(
      base::Bind(&ConnectionToClient::OnSessionStateChange,
                 base::Unretained(this)));
 }

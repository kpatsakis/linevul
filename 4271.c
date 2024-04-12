WebContext::~WebContext() {
  if (context_.get()) {
    context_->SetDelegate(nullptr);
    MediaCaptureDevicesContext::Get(context_.get())->set_client(nullptr);
  }
 }

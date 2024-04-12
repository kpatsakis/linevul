HeadlessWebContentsImpl::~HeadlessWebContentsImpl() {
  agent_host_->RemoveObserver(this);
  if (render_process_host_)
    render_process_host_->RemoveObserver(this);
  if (begin_frame_control_enabled_) {
    ui::Compositor* compositor = browser()->PlatformGetCompositor(this);
    DCHECK(compositor);
    compositor->SetExternalBeginFrameClient(nullptr);
  }
}

 void ChromotingInstance::Disconnect() {
   DCHECK(plugin_task_runner_->BelongsToCurrentThread());
 
  VLOG(0) << "Disconnecting from host.";

  mouse_input_filter_.set_input_stub(nullptr);
  client_.reset();
  video_renderer_.reset();
}

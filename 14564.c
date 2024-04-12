void CommandBufferProxyImpl::SetUpdateVSyncParametersCallback(
    const UpdateVSyncParametersCallback& callback) {
  CheckLock();
  update_vsync_parameters_completion_callback_ = callback;
}

void WebPluginDelegateProxy::DestroyCommandBuffer(
    CommandBufferProxy* command_buffer) {
  DCHECK(command_buffer);
#if defined(ENABLE_GPU)
  Send(new PluginMsg_DestroyCommandBuffer(instance_id_));
  channel_host_->RemoveRoute(command_buffer->route_id());
  delete command_buffer;
#endif
}

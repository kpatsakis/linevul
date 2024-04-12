void RenderMessageFilter::OnOpenChannelToPpapiBroker(int routing_id,
                                                     int request_id,
                                                     const FilePath& path) {
  plugin_service_->OpenChannelToPpapiBroker(
      render_process_id_,
      path,
      new OpenChannelToPpapiBrokerCallback(this, routing_id, request_id));
}

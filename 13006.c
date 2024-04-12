  void DidReceiveResponse(const std::string& mime_type,
                          const std::string& headers,
                          uint32 expected_length,
                          uint32 last_modified,
                          bool request_is_seekable) {
    DCHECK(channel_ != NULL);
    PluginMsg_DidReceiveResponseParams params;
    params.id = resource_id_;
    params.mime_type = mime_type;
    params.headers = headers;
    params.expected_length = expected_length;
    params.last_modified = last_modified;
    params.request_is_seekable = request_is_seekable;
    scoped_refptr<PluginChannelHost> channel_ref(channel_);
    channel_->Send(new PluginMsg_DidReceiveResponse(instance_id_, params));
  }

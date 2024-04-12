  void DidReceiveData(const char* buffer, int length, int data_offset) {
    DCHECK(channel_ != NULL);
    DCHECK_GT(length, 0);
    std::vector<char> data;
    data.resize(static_cast<size_t>(length));
    memcpy(&data.front(), buffer, length);
    scoped_refptr<PluginChannelHost> channel_ref(channel_);
    channel_->Send(new PluginMsg_DidReceiveData(instance_id_, resource_id_,
                                                data, data_offset));
  }

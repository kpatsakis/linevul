  void AddRootItemWithPosition(int64 position) {
    string id = string("ServerId") + base::Int64ToString(next_update_id_++);
    string name = "my name is my id -- " + id;
    int revision = next_revision_++;
    mock_server_->AddUpdateDirectory(id, kRootId, name, revision, revision);
    mock_server_->SetLastUpdatePosition(position);
    position_map_.insert(
        PosMap::value_type(position, Id::CreateFromServerId(id)));
  }

GLES2Implementation::~GLES2Implementation() {
  WaitForCmd();

  query_tracker_.reset();

  if (support_client_side_arrays_ && reserved_ids_[0]) {
    DeleteBuffers(base::size(reserved_ids_), &reserved_ids_[0]);
  }

  ClearMappedBufferRangeMap();

  share_group_->FreeContext(this);

  buffer_tracker_.reset();
  readback_buffer_shadow_tracker_.reset();

  WaitForCmd();
}

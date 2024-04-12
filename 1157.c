void GLES2Implementation::InsertEventMarkerEXT(GLsizei length,
                                               const GLchar* marker) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glInsertEventMarkerEXT(" << length
                     << ", " << marker << ")");
  if (!marker) {
    marker = "";
  }
  SetBucketAsString(kResultBucketId, (length ? std::string(marker, length)
                                             : std::string(marker)));
  helper_->InsertEventMarkerEXT(kResultBucketId);
  helper_->SetBucketSize(kResultBucketId, 0);
  debug_marker_manager_.SetMarker(length ? std::string(marker, length)
                                         : std::string(marker));
}

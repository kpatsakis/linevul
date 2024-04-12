TextureManager::TextureInfo::TextureInfo(TextureManager* manager,
                                         GLuint service_id)
    : manager_(manager),
      service_id_(service_id),
      deleted_(false),
      cleared_(true),
      num_uncleared_mips_(0),
      target_(0),
      min_filter_(GL_NEAREST_MIPMAP_LINEAR),
      mag_filter_(GL_LINEAR),
      wrap_s_(GL_REPEAT),
      wrap_t_(GL_REPEAT),
      usage_(GL_NONE),
      max_level_set_(-1),
      texture_complete_(false),
      cube_complete_(false),
      npot_(false),
      has_been_bound_(false),
      framebuffer_attachment_count_(0),
      owned_(true),
      stream_texture_(false),
      immutable_(false),
      estimated_size_(0) {
  if (manager_) {
    manager_->StartTracking(this);
  }
}

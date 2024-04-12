void MultibufferDataSource::CreateResourceLoader_Locked(
    int64_t first_byte_position,
    int64_t last_byte_position) {
  DCHECK(render_task_runner_->BelongsToCurrentThread());
  lock_.AssertAcquired();

  reader_.reset(new MultiBufferReader(
      url_data()->multibuffer(), first_byte_position, last_byte_position,
      base::Bind(&MultibufferDataSource::ProgressCallback, weak_ptr_)));
  UpdateBufferSizes();
}

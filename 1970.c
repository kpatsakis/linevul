void MultibufferDataSource::CreateResourceLoader(int64_t first_byte_position,
                                                 int64_t last_byte_position) {
  DCHECK(render_task_runner_->BelongsToCurrentThread());

  SetReader(new MultiBufferReader(
      url_data()->multibuffer(), first_byte_position, last_byte_position,
      base::Bind(&MultibufferDataSource::ProgressCallback, weak_ptr_)));
  reader_->SetIsClientAudioElement(is_client_audio_element_);
  UpdateBufferSizes();
}

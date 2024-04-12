void WebMediaPlayerImpl::OnAudioConfigChange(const AudioDecoderConfig& config) {
  DCHECK(main_task_runner_->BelongsToCurrentThread());
  DCHECK_NE(ready_state_, WebMediaPlayer::kReadyStateHaveNothing);

  const bool codec_change =
      pipeline_metadata_.audio_decoder_config.codec() != config.codec();
  pipeline_metadata_.audio_decoder_config = config;

  if (observer_)
    observer_->OnMetadataChanged(pipeline_metadata_);

  if (codec_change)
    UpdateSecondaryProperties();
}

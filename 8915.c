void WebMediaPlayerImpl::UpdateRemotePlaybackCompatibility(bool is_compatible) {
  DCHECK(main_task_runner_->BelongsToCurrentThread());

  client_->RemotePlaybackCompatibilityChanged(loaded_url_, is_compatible);
}

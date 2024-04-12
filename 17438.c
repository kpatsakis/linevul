 void AudioSystemImpl::HasInputDevices(OnBoolCallback on_has_devices_cb) const {
   if (GetTaskRunner()->BelongsToCurrentThread()) {
     GetTaskRunner()->PostTask(
        FROM_HERE,
        base::Bind(on_has_devices_cb, audio_manager_->HasAudioInputDevices()));
    return;
  }
  base::PostTaskAndReplyWithResult(
      GetTaskRunner(), FROM_HERE,
      base::Bind(&AudioManager::HasAudioInputDevices,
                 base::Unretained(audio_manager_)),
      std::move(on_has_devices_cb));
}

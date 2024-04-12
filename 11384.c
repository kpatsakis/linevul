void AudioMixerAlsa::GetVolumeLimits(double* min_volume_db,
                                     double* max_volume_db) {
  base::AutoLock lock(lock_);
  if (min_volume_db)
    *min_volume_db = min_volume_db_;
  if (max_volume_db)
    *max_volume_db = max_volume_db_;
}

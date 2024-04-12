SiteFeatureUsage LocalSiteCharacteristicsDataImpl::UsesAudioInBackground()
    const {
  return GetFeatureUsage(
      site_characteristics_.uses_audio_in_background(),
      GetSiteCharacteristicsDatabaseParams().audio_usage_observation_window);
}

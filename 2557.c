std::vector<SiteCharacteristicsFeatureProto*> GetAllFeaturesFromProto(
    SiteCharacteristicsProto* proto) {
  std::vector<SiteCharacteristicsFeatureProto*> ret(
      {proto->mutable_updates_favicon_in_background(),
       proto->mutable_updates_title_in_background(),
       proto->mutable_uses_audio_in_background(),
       proto->mutable_uses_notifications_in_background()});

  return ret;
}

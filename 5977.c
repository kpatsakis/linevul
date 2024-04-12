void LocalSiteCharacteristicsDataImpl::OnInitCallback(
    base::Optional<SiteCharacteristicsProto> db_site_characteristics) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  if (db_site_characteristics) {
    auto this_features = GetAllFeaturesFromProto(&site_characteristics_);
    auto db_features =
        GetAllFeaturesFromProto(&db_site_characteristics.value());
    auto this_features_iter = this_features.begin();
    auto db_features_iter = db_features.begin();
    for (; this_features_iter != this_features.end() &&
           db_features_iter != db_features.end();
         ++this_features_iter, ++db_features_iter) {
      if (!(*this_features_iter)->has_use_timestamp()) {
        if ((*db_features_iter)->has_use_timestamp()) {
          (*this_features_iter)
              ->set_use_timestamp((*db_features_iter)->use_timestamp());
          (*this_features_iter)
              ->set_observation_duration(
                  LocalSiteCharacteristicsDataImpl::
                      TimeDeltaToInternalRepresentation(base::TimeDelta()));
        } else {
          if (!(*this_features_iter)->has_observation_duration()) {
            (*this_features_iter)
                ->set_observation_duration(
                    LocalSiteCharacteristicsDataImpl::
                        TimeDeltaToInternalRepresentation(base::TimeDelta()));
          }
          IncrementFeatureObservationDuration(
              (*this_features_iter),
              InternalRepresentationToTimeDelta(
                  (*db_features_iter)->observation_duration()));
        }
      }
    }
    if (!site_characteristics_.has_last_loaded()) {
      site_characteristics_.set_last_loaded(
          db_site_characteristics->last_loaded());
    }
  } else {
    InitWithDefaultValues(true /* only_init_uninitialized_fields */);
  }

  safe_to_write_to_db_ = true;
  DCHECK(site_characteristics_.IsInitialized());
}

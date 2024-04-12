void SyncManager::TriggerOnIncomingNotificationForTest(
    const syncable::ModelTypeBitSet& model_types) {
  syncable::ModelTypePayloadMap model_types_with_payloads =
      syncable::ModelTypePayloadMapFromBitSet(model_types,
          std::string());

  data_->OnIncomingNotification(model_types_with_payloads);
}

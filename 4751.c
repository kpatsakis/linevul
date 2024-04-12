void SyncBackendHost::SetAutofillMigrationDebugInfo(
    syncable::AutofillMigrationDebugInfo::PropertyToSet property_to_set,
    const syncable::AutofillMigrationDebugInfo& info) {
  return core_->syncapi()->SetAutofillMigrationDebugInfo(property_to_set, info);
}

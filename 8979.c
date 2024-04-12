void ProfileSyncService::ChangePreferredDataTypes(
    syncable::ModelTypeSet preferred_types) {

  DVLOG(1) << "ChangePreferredDataTypes invoked";
  const syncable::ModelTypeSet registered_types = GetRegisteredDataTypes();
  const syncable::ModelTypeSet registered_preferred_types =
      Intersection(registered_types, preferred_types);
  sync_prefs_.SetPreferredDataTypes(registered_types,
                                    registered_preferred_types);

  ReconfigureDatatypeManager();
}

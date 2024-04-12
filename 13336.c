void ProfileSyncService::UpdateSelectedTypesHistogram(
    bool sync_everything, const syncable::ModelTypeSet chosen_types) const {
  if (!HasSyncSetupCompleted() ||
      sync_everything != sync_prefs_.HasKeepEverythingSynced()) {
    UMA_HISTOGRAM_BOOLEAN("Sync.SyncEverything", sync_everything);
  }

  const syncable::ModelType model_types[] = {
    syncable::APPS,
    syncable::AUTOFILL,
    syncable::BOOKMARKS,
    syncable::EXTENSIONS,
    syncable::PASSWORDS,
    syncable::PREFERENCES,
    syncable::SESSIONS,
    syncable::THEMES,
    syncable::TYPED_URLS
  };

  const browser_sync::user_selectable_type::UserSelectableSyncType
      user_selectable_types[] = {
    browser_sync::user_selectable_type::APPS,
    browser_sync::user_selectable_type::AUTOFILL,
    browser_sync::user_selectable_type::BOOKMARKS,
    browser_sync::user_selectable_type::EXTENSIONS,
    browser_sync::user_selectable_type::PASSWORDS,
    browser_sync::user_selectable_type::PREFERENCES,
    browser_sync::user_selectable_type::SESSIONS,
    browser_sync::user_selectable_type::THEMES,
    browser_sync::user_selectable_type::TYPED_URLS
  };

  COMPILE_ASSERT(17 == syncable::MODEL_TYPE_COUNT,
                 UpdateCustomConfigHistogram);
  COMPILE_ASSERT(arraysize(model_types) ==
                 browser_sync::user_selectable_type::SELECTABLE_DATATYPE_COUNT,
                 UpdateCustomConfigHistogram);
  COMPILE_ASSERT(arraysize(model_types) == arraysize(user_selectable_types),
                 UpdateCustomConfigHistogram);

  if (!sync_everything) {
    const syncable::ModelTypeSet current_types = GetPreferredDataTypes();
    for (size_t i = 0; i < arraysize(model_types); ++i) {
      const syncable::ModelType type = model_types[i];
      if (chosen_types.Has(type) &&
          (!HasSyncSetupCompleted() || !current_types.Has(type))) {
        UMA_HISTOGRAM_ENUMERATION(
            "Sync.CustomSync",
            user_selectable_types[i],
            browser_sync::user_selectable_type::SELECTABLE_DATATYPE_COUNT + 1);
      }
    }
  }
}

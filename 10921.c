  void RecheckGDataOperations() {
    Profile* profile = ProfileManager::GetDefaultProfile();
    if (!gdata::util::IsGDataAvailable(profile))
      return;

    GDataSystemService* system_service =
          GDataSystemServiceFactory::FindForProfile(profile);
    if (!system_service || !system_service->file_system())
      return;

    OnProgressUpdate(system_service->file_system()->GetOperationRegistry()->
        GetProgressStatusList());
  }

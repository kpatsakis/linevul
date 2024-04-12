const MasterPreferences& MasterPreferences::ForCurrentProcess() {
  return g_master_preferences.Get();
}

void PeopleHandler::OnJavascriptDisallowed() {
  profile_pref_registrar_.RemoveAll();
  identity_manager_observer_.RemoveAll();
  sync_service_observer_.RemoveAll();
#if BUILDFLAG(ENABLE_DICE_SUPPORT)
  account_tracker_observer_.RemoveAll();
#endif
}

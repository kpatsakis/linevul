SupervisedUserService::SupervisedUserService(Profile* profile)
    : profile_(profile),
      active_(false),
      delegate_(NULL),
      is_profile_active_(false),
      did_init_(false),
      did_shutdown_(false),
      blacklist_state_(BlacklistLoadState::NOT_LOADED),
#if BUILDFLAG(ENABLE_EXTENSIONS)
      registry_observer_(this),
#endif
      weak_ptr_factory_(this) {
  url_filter_.AddObserver(this);
#if BUILDFLAG(ENABLE_EXTENSIONS)
  registry_observer_.Add(extensions::ExtensionRegistry::Get(profile));
#endif
}

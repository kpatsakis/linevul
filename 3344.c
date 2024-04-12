void ProfileDependencyManager::DestroyProfileServices(Profile* profile) {
  if (destruction_order_.empty())
    BuildDestructionOrder(profile);

  for (std::vector<ProfileKeyedBaseFactory*>::const_iterator it =
           destruction_order_.begin(); it != destruction_order_.end(); ++it) {
    (*it)->ProfileShutdown(profile);
  }

#ifndef NDEBUG
  dead_profile_pointers_.insert(profile);
#endif

  for (std::vector<ProfileKeyedBaseFactory*>::const_iterator it =
           destruction_order_.begin(); it != destruction_order_.end(); ++it) {
    (*it)->ProfileDestroyed(profile);
  }
}

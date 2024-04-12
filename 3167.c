void RegistrationManager::MarkRegistrationLost(
    const invalidation::ObjectId& id) {
  DCHECK(CalledOnValidThread());
  RegistrationStatusMap::const_iterator it = registration_statuses_.find(id);
  if (it == registration_statuses_.end()) {
    DLOG(WARNING) << "Attempt to mark non-existent registration for "
                  << ObjectIdToString(id) << " as lost";
    return;
  }
  if (!it->second->enabled) {
    return;
  }
  it->second->state = invalidation::InvalidationListener::UNREGISTERED;
  bool is_retry = !it->second->last_registration_request.is_null();
  TryRegisterId(id, is_retry);
}

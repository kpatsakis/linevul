void RegistrationManager::DoRegisterId(const invalidation::ObjectId& id) {
  DCHECK(CalledOnValidThread());
  invalidation_client_->Register(id);
  RegistrationStatusMap::const_iterator it = registration_statuses_.find(id);
  if (it == registration_statuses_.end()) {
    DLOG(FATAL) << "DoRegisterId called on " << ObjectIdToString(id)
                << " which is not in the registration map";
    return;
  }
  it->second->state = invalidation::InvalidationListener::REGISTERED;
  it->second->last_registration_request = base::Time::Now();
}

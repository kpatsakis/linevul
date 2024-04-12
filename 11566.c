void RegistrationManager::RegistrationStatus::Disable() {
  enabled = false;
  state = invalidation::InvalidationListener::UNREGISTERED;
  registration_timer.Stop();
  delay = base::TimeDelta();
}

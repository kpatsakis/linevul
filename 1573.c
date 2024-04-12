void RegistrationManager::RegistrationStatus::DoRegister() {
  CHECK(enabled);
  registration_timer.Stop();
  delay = base::TimeDelta();
  registration_manager->DoRegisterId(id);
  DCHECK(!last_registration_request.is_null());
}

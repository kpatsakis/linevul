ForeignSessionHelper::ForeignSessionHelper(Profile* profile)
    : profile_(profile) {
  sync_sessions::SessionSyncService* service =
      SessionSyncServiceFactory::GetInstance()->GetForProfile(profile);

  if (service) {
    foreign_session_updated_subscription_ =
        service->SubscribeToForeignSessionsChanged(base::BindRepeating(
            &ForeignSessionHelper::FireForeignSessionCallback,
            base::Unretained(this)));
  }
}

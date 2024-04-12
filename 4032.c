BaseSessionService::BaseSessionService(SessionType type,
                                       Profile* profile,
                                       const FilePath& path)
    : profile_(profile),
      path_(path),
      ALLOW_THIS_IN_INITIALIZER_LIST(weak_factory_(this)),
      pending_reset_(false),
      commands_since_reset_(0),
      save_post_data_(false) {
  if (profile) {
    DCHECK(!profile->IsOffTheRecord());
    const CommandLine* command_line = CommandLine::ForCurrentProcess();
    save_post_data_ =
        !command_line->HasSwitch(switches::kDisableRestoreSessionState);
  }
  backend_ = new SessionBackend(type,
      profile_ ? profile_->GetPath() : path_);
  DCHECK(backend_.get());

  if (!RunningInProduction()) {
    backend_->Init();
  }
}

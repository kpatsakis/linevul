void SyncBackendHost::StartConfiguration(Callback0::Type* callback) {
  core_thread_.message_loop()->PostTask(FROM_HERE, NewRunnableMethod(
    core_.get(),&SyncBackendHost::Core::DoStartConfiguration, callback));
}

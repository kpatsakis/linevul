void SyncBackendHost::EnableEncryptEverything() {
  sync_thread_.message_loop()->PostTask(FROM_HERE,
     NewRunnableMethod(core_.get(),
                       &SyncBackendHost::Core::DoEnableEncryptEverything));
}

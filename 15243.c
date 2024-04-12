void SyncBackendHost::Core::SetParentJsEventRouter(JsEventRouter* router) {
  DCHECK_EQ(MessageLoop::current(), host_->frontend_loop_);
  DCHECK(router);
  parent_router_ = router;
  MessageLoop* core_message_loop = host_->core_thread_.message_loop();
  CHECK(core_message_loop);
  core_message_loop->PostTask(
      FROM_HERE,
      NewRunnableMethod(this,
                        &SyncBackendHost::Core::ConnectChildJsEventRouter));
}

void SyncBackendHost::Core::RouteJsEvent(
    const std::string& name, const JsEventDetails& details) {
  host_->frontend_loop_->PostTask(
      FROM_HERE, NewRunnableMethod(
          this, &Core::RouteJsEventOnFrontendLoop, name, details));
}

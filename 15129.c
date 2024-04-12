Response ServiceWorkerHandler::Unregister(const std::string& scope_url) {
  if (!enabled_)
    return CreateDomainNotEnabledErrorResponse();
  if (!context_)
    return CreateContextErrorResponse();
  context_->UnregisterServiceWorker(GURL(scope_url), base::Bind(&ResultNoOp));
  return Response::OK();
}

int Document::RequestIdleCallback(IdleRequestCallback* callback,
                                  const IdleRequestOptions& options) {
  return EnsureScriptedIdleTaskController().RegisterCallback(callback, options);
}

int LocalDOMWindow::requestIdleCallback(V8IdleRequestCallback* callback,
                                        const IdleRequestOptions& options) {
  if (Document* document = this->document()) {
    return document->RequestIdleCallback(
        ScriptedIdleTaskController::V8IdleTask::Create(callback), options);
  }
  return 0;
}

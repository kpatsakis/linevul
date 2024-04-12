CreateContextProviderOnWorkerThread(
    Platform::ContextAttributes context_attributes,
    Platform::GraphicsInfo* gl_info,
    const KURL& url) {
  WaitableEvent waitable_event;
  ContextProviderCreationInfo creation_info;
  creation_info.context_attributes = context_attributes;
  creation_info.gl_info = gl_info;
  creation_info.url = url.Copy();
  RefPtr<WebTaskRunner> task_runner =
      Platform::Current()->MainThread()->GetWebTaskRunner();
  task_runner->PostTask(
      BLINK_FROM_HERE, CrossThreadBind(&CreateContextProviderOnMainThread,
                                       CrossThreadUnretained(&creation_info),
                                       CrossThreadUnretained(&waitable_event)));
  waitable_event.Wait();
  return std::move(creation_info.created_context_provider);
}

void IndexedDBDispatcher::RequestIDBFactoryOpen(
    const string16& name,
    WebIDBCallbacks* callbacks_ptr,
    const string16& origin,
    WebFrame* web_frame) {
  ResetCursorPrefetchCaches();
  scoped_ptr<WebIDBCallbacks> callbacks(callbacks_ptr);

  if (!CurrentWorkerId() &&
      !ChildThread::current()->IsWebFrameValid(web_frame))
    return;

  IndexedDBHostMsg_FactoryOpen_Params params;
  params.thread_id = CurrentWorkerId();
  params.response_id = pending_callbacks_.Add(callbacks.release());
  params.origin = origin;
  params.name = name;
  Send(new IndexedDBHostMsg_FactoryOpen(params));
}

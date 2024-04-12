void WebLocalFrameImpl::RequestExecuteScriptAndReturnValue(
    const WebScriptSource& source,
    bool user_gesture,
    WebScriptExecutionCallback* callback) {
  DCHECK(GetFrame());

  RefPtr<DOMWrapperWorld> main_world = &DOMWrapperWorld::MainWorld();
  SuspendableScriptExecutor* executor = SuspendableScriptExecutor::Create(
      GetFrame(), std::move(main_world), CreateSourcesVector(&source, 1),
      user_gesture, callback);
  executor->Run();
}

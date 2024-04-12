bool FrameLoader::PrepareForCommit() {
  PluginScriptForbiddenScope forbid_plugin_destructor_scripting;
  DocumentLoader* pdl = provisional_document_loader_;

  if (frame_->GetDocument()) {
    unsigned node_count = 0;
    for (Frame* frame = frame_; frame; frame = frame->Tree().TraverseNext()) {
      if (frame->IsLocalFrame()) {
        LocalFrame* local_frame = ToLocalFrame(frame);
        node_count += local_frame->GetDocument()->NodeCount();
      }
    }
    unsigned total_node_count =
        InstanceCounters::CounterValue(InstanceCounters::kNodeCounter);
    float ratio = static_cast<float>(node_count) / total_node_count;
    ThreadState::Current()->SchedulePageNavigationGCIfNeeded(ratio);
  }

  SubframeLoadingDisabler disabler(frame_->GetDocument());
  IgnoreOpensDuringUnloadCountIncrementer ignore_opens_during_unload(
      frame_->GetDocument());
  if (document_loader_) {
    Client()->DispatchWillCommitProvisionalLoad();
    DispatchUnloadEvent();
  }
  frame_->DetachChildren();
  if (pdl != provisional_document_loader_)
    return false;
  if (document_loader_) {
    base::AutoReset<bool> in_detach_document_loader(
        &protect_provisional_loader_, true);
    DetachDocumentLoader(document_loader_, true);
  }
  if (!frame_->Client())
    return false;
  DCHECK_EQ(provisional_document_loader_, pdl);

  if (frame_->GetDocument())
    frame_->GetDocument()->Shutdown();
  document_loader_ = provisional_document_loader_.Release();
  if (document_loader_)
    document_loader_->MarkAsCommitted();

  TakeObjectSnapshot();

  return true;
}

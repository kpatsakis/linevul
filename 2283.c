void WebLocalFrameImpl::InitializeCoreFrame(Page& page,
                                            FrameOwner* owner,
                                            const AtomicString& name) {
  SetCoreFrame(LocalFrame::Create(local_frame_client_.Get(), page, owner,
                                  interface_registry_));
  frame_->Tree().SetName(name);
  frame_->Init();
  CHECK(frame_);
  CHECK(frame_->Loader().StateMachine()->IsDisplayingInitialEmptyDocument());
  if (!Parent() && !Opener() &&
      frame_->GetSettings()->GetShouldReuseGlobalForUnownedMainFrame()) {
    frame_->GetDocument()->GetMutableSecurityOrigin()->GrantUniversalAccess();
  }

  if (frame_->IsLocalRoot()) {
    frame_->GetInterfaceRegistry()->AddAssociatedInterface(
        WTF::BindRepeating(&WebLocalFrameImpl::BindDevToolsAgentRequest,
                           WrapWeakPersistent(this)));
  }

  if (!owner) {
    TRACE_EVENT_INSTANT1("loading", "markAsMainFrame", TRACE_EVENT_SCOPE_THREAD,
                         "frame", ToTraceValue(frame_));
  }
}

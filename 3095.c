void LocalFrame::Detach(FrameDetachType type) {

  DCHECK_NE(lifecycle_.GetState(), FrameLifecycle::kDetached);
  lifecycle_.AdvanceTo(FrameLifecycle::kDetaching);

  if (IsLocalRoot()) {
    performance_monitor_->Shutdown();
    ad_tracker_->Shutdown();
  }
  idleness_detector_->Shutdown();
  if (inspector_trace_events_)
    probe_sink_->removeInspectorTraceEvents(inspector_trace_events_);
  inspector_task_runner_->Dispose();

  PluginScriptForbiddenScope forbid_plugin_destructor_scripting;
  loader_.StopAllLoaders();
  SubframeLoadingDisabler disabler(*GetDocument());
  loader_.DispatchUnloadEvent();
  DetachChildren();

  if (!Client())
    return;

  loader_.StopAllLoaders();
  loader_.Detach();
  GetDocument()->Shutdown();
  if (view_ && view_->IsAttached()) {
    CHECK(DeprecatedLocalOwner());
    CHECK(DeprecatedLocalOwner()->OwnedEmbeddedContentView());
    CHECK_EQ(view_, DeprecatedLocalOwner()->OwnedEmbeddedContentView());
  }
  CHECK(!view_ || !view_->IsAttached());

  ScriptForbiddenScope forbid_script;
  if (!Client())
    return;

  DCHECK_NE(lifecycle_.GetState(), FrameLifecycle::kDetached);

  CHECK(!view_->IsAttached());
  Client()->WillBeDetached();
  GetScriptController().ClearForClose();

  CHECK(!view_->IsAttached());
  SetView(nullptr);

  GetEventHandlerRegistry().DidRemoveAllEventHandlers(*DomWindow());

  DomWindow()->FrameDestroyed();

  if (GetPage() && GetPage()->GetFocusController().FocusedFrame() == this)
    GetPage()->GetFocusController().SetFocusedFrame(nullptr);

  probe::frameDetachedFromParent(this);

  supplements_.clear();
  frame_scheduler_.reset();
  WeakIdentifierMap<LocalFrame>::NotifyObjectDestroyed(this);
  Frame::Detach(type);
}

void Document::CheckCompleted() {
  if (!ShouldComplete())
    return;

  if (frame_) {
    frame_->Client()->RunScriptsAtDocumentIdle();

    if (!frame_)
      return;

    if (!ShouldComplete())
      return;
  }

  SetReadyState(kComplete);
  if (LoadEventStillNeeded())
    ImplicitClose();

  if (!frame_ || !frame_->IsAttached())
    return;
  if (frame_->GetSettings()->GetSavePreviousDocumentResources() ==
      SavePreviousDocumentResources::kUntilOnLoad) {
    fetcher_->ClearResourcesFromPreviousFetcher();
  }
  frame_->GetNavigationScheduler().StartTimer();
  View()->HandleLoadCompleted();
  if (!AllDescendantsAreComplete(frame_))
    return;

  if (!Loader()->SentDidFinishLoad()) {
    if (frame_->IsMainFrame())
      GetViewportDescription().ReportMobilePageStats(frame_);
    Loader()->SetSentDidFinishLoad();
    frame_->Client()->DispatchDidFinishLoad();
    if (!frame_)
      return;

    if (frame_->Client()->GetRemoteNavigationAssociatedInterfaces()) {
      mojom::blink::UkmSourceIdFrameHostAssociatedPtr ukm_binding;
      frame_->Client()->GetRemoteNavigationAssociatedInterfaces()->GetInterface(
          &ukm_binding);
      DCHECK(ukm_binding.is_bound());
      ukm_binding->SetDocumentSourceId(ukm_source_id_);
    }
  }

  frame_->Loader().DidFinishNavigation();
}

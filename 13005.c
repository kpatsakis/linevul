void FrameLoader::DidFinishNavigation() {
  DCHECK((document_loader_ && document_loader_->SentDidFinishLoad()) ||
         !HasProvisionalNavigation());
  if (!document_loader_ || !document_loader_->SentDidFinishLoad() ||
      HasProvisionalNavigation()) {
    return;
  }

  if (frame_->IsLoading()) {
    progress_tracker_->ProgressCompleted();
    RestoreScrollPositionAndViewState();
    if (document_loader_)
      document_loader_->SetLoadType(kFrameLoadTypeStandard);
    frame_->DomWindow()->FinishedLoading();
  }

  Frame* parent = frame_->Tree().Parent();
  if (parent && parent->IsLocalFrame())
    ToLocalFrame(parent)->GetDocument()->CheckCompleted();
}

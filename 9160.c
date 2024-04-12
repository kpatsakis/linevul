void DocumentLoader::LoadFailed(const ResourceError& error) {
  if (!error.IsCancellation() && frame_->Owner())
    frame_->Owner()->RenderFallbackContent(frame_);
  fetcher_->ClearResourcesFromPreviousFetcher();

  WebHistoryCommitType history_commit_type = LoadTypeToCommitType(load_type_);
  switch (state_) {
    case kNotStarted:
      FALLTHROUGH;
    case kProvisional:
      state_ = kSentDidFinishLoad;
      GetLocalFrameClient().DispatchDidFailProvisionalLoad(error,
                                                           history_commit_type);
      probe::didFailProvisionalLoad(frame_);
      if (frame_)
        GetFrameLoader().DetachProvisionalDocumentLoader(this);
      break;
    case kCommitted:
      if (frame_->GetDocument()->Parser())
        frame_->GetDocument()->Parser()->StopParsing();
      state_ = kSentDidFinishLoad;
      GetLocalFrameClient().DispatchDidFailLoad(error, history_commit_type);
      GetFrameLoader().DidFinishNavigation();
      break;
    case kSentDidFinishLoad:
      NOTREACHED();
      break;
  }
  DCHECK_EQ(kSentDidFinishLoad, state_);
}

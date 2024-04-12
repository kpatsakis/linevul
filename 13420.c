void LocalFrame::ForceSynchronousDocumentInstall(
    const AtomicString& mime_type,
    scoped_refptr<SharedBuffer> data) {
  CHECK(loader_.StateMachine()->IsDisplayingInitialEmptyDocument());
  DCHECK(!Client()->IsLocalFrameClientImpl());

  GetDocument()->Shutdown();

  DomWindow()->InstallNewDocument(
      mime_type, DocumentInit::Create().WithFrame(this), false);
  loader_.StateMachine()->AdvanceTo(
      FrameLoaderStateMachine::kCommittedFirstRealLoad);

  GetDocument()->OpenForNavigation(kForceSynchronousParsing, mime_type,
                                   AtomicString("UTF-8"));
  data->ForEachSegment(
      [this](const char* segment, size_t segment_size, size_t segment_offset) {
        GetDocument()->Parser()->AppendBytes(segment, segment_size);
        return true;
      });
  GetDocument()->Parser()->Finish();

  if (GetPage() && GetDocument()->IsSVGDocument())
    GetPage()->GetUseCounter().DidCommitLoad(this);
}

void Document::open() {
  DCHECK(!ImportLoader());

  if (frame_) {
    if (ScriptableDocumentParser* parser = GetScriptableDocumentParser()) {
      if (parser->IsParsing()) {
        if (parser->IsExecutingScript())
          return;

        if (!parser->WasCreatedByScript() && parser->HasInsertionPoint())
          return;
      }
    }

    if (frame_->Loader().HasProvisionalNavigation()) {
      frame_->Loader().StopAllLoaders();
      if (frame_->Client() &&
          frame_->GetSettings()->GetBrowserSideNavigationEnabled()) {
        frame_->Client()->AbortClientNavigation();
      }
    }
  }

  RemoveAllEventListenersRecursively();
  ResetTreeScope();
  if (frame_)
    frame_->Selection().Clear();
  ImplicitOpen(kForceSynchronousParsing);
  if (ScriptableDocumentParser* parser = GetScriptableDocumentParser())
    parser->SetWasCreatedByScript(true);

  if (frame_)
    frame_->Loader().DidExplicitOpen();
}

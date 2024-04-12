void FrameLoader::ReplaceDocumentWhileExecutingJavaScriptURL(
    const String& source,
    Document* owner_document) {
  Document* document = frame_->GetDocument();
  if (!document_loader_ ||
      document->PageDismissalEventBeingDispatched() != Document::kNoDismissal)
    return;

  UseCounter::Count(*document, WebFeature::kReplaceDocumentViaJavaScriptURL);

  const KURL& url = document->Url();

  WebGlobalObjectReusePolicy global_object_reuse_policy =
      frame_->ShouldReuseDefaultView(url, document->GetContentSecurityPolicy())
          ? WebGlobalObjectReusePolicy::kUseExisting
          : WebGlobalObjectReusePolicy::kCreateNew;

  StopAllLoaders();
  SubframeLoadingDisabler disabler(document);
  IgnoreOpensDuringUnloadCountIncrementer ignore_opens_during_unload(document);
  frame_->DetachChildren();

  if (!frame_->IsAttached() || document != frame_->GetDocument())
    return;

  frame_->GetDocument()->Shutdown();
  Client()->TransitionToCommittedForNewPage();
  document_loader_->ReplaceDocumentWhileExecutingJavaScriptURL(
      url, owner_document, global_object_reuse_policy, source);
}

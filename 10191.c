bool ContentSecurityPolicy::ShouldBypassMainWorld(
    const ExecutionContext* context) {
  if (const auto* document = DynamicTo<Document>(context)) {
    if (document->GetFrame()) {
      return document->GetFrame()
          ->GetScriptController()
          .ShouldBypassMainWorldCSP();
    }
  }
  return false;
}

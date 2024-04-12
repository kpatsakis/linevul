bool Document::IsRenderingReady() const {
  return style_engine_->IgnoringPendingStylesheets() ||
         (HaveImportsLoaded() && HaveRenderBlockingStylesheetsLoaded());
}

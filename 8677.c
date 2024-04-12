void PrintRenderFrameHelper::PrepareFrameForPreviewDocument() {
  reset_prep_frame_view_ = false;

  if (!print_pages_params_ || CheckForCancel()) {
    DidFinishPrinting(FAIL_PREVIEW);
    return;
  }

  if (prep_frame_view_ && prep_frame_view_->IsLoadingSelection()) {
    reset_prep_frame_view_ = true;
    return;
  }

  const PrintMsg_Print_Params& print_params = print_pages_params_->params;
  prep_frame_view_ = base::MakeUnique<PrepareFrameAndViewForPrint>(
      print_params, print_preview_context_.source_frame(),
      print_preview_context_.source_node(), ignore_css_margins_);
  prep_frame_view_->CopySelectionIfNeeded(
      render_frame()->GetWebkitPreferences(),
      base::Bind(&PrintRenderFrameHelper::OnFramePreparedForPreviewDocument,
                 weak_ptr_factory_.GetWeakPtr()));
}

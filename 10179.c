void PrintRenderFrameHelper::PrintPages() {
  if (!prep_frame_view_)  // Printing is already canceled or failed.
    return;

  prep_frame_view_->StartPrinting();

  int page_count = prep_frame_view_->GetExpectedPageCount();
  if (!page_count) {
    LOG(ERROR) << "Can't print 0 pages.";
    return DidFinishPrinting(FAIL_PRINT);
  }

  const PrintMsg_PrintPages_Params& params = *print_pages_params_;
  const PrintMsg_Print_Params& print_params = params.params;

#if !defined(OS_ANDROID)
  Send(new PrintHostMsg_DidGetPrintedPagesCount(
      routing_id(), print_params.document_cookie, page_count));
#endif  // !defined(OS_ANDROID)

  if (print_params.preview_ui_id < 0) {
    int printed_count = params.pages.empty() ? page_count : params.pages.size();
    UMA_HISTOGRAM_COUNTS("PrintPreview.PageCount.SystemDialog", printed_count);
  }

  if (!PrintPagesNative(prep_frame_view_->frame(), page_count)) {
    LOG(ERROR) << "Printing failed.";
    return DidFinishPrinting(FAIL_PRINT);
  }
}

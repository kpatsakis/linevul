void PrintWebViewHelper::RenderPagesForPrint(WebFrame* frame,
                                             WebNode* node) {
  ViewMsg_PrintPages_Params print_settings = *print_pages_params_;
  if (print_settings.params.selection_only) {
    CopyAndPrint(frame);
  } else {
    PrintPages(print_settings, frame, node);
  }
}

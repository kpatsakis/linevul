void PrintWebViewHelper::UpdateFrameAndViewFromCssPageLayout(
    WebFrame* frame,
    const WebNode& node,
    PrepareFrameAndViewForPrint* prepare,
    const PrintMsg_Print_Params& params,
    bool ignore_css_margins) {
  if (PrintingNodeOrPdfFrame(frame, node))
    return;
  PrintMsg_Print_Params print_params = CalculatePrintParamsForCss(
      frame, 0, params, ignore_css_margins,
      ignore_css_margins && params.fit_to_paper_size, NULL);
  prepare->UpdatePrintParams(print_params);
}

PrepareFrameAndViewForPrint::PrepareFrameAndViewForPrint(
    const PrintMsg_Print_Params& params,
    blink::WebLocalFrame* frame,
    const blink::WebNode& node,
    bool ignore_css_margins)
    : frame_(frame),
      node_to_print_(node),
      owns_web_view_(false),
      expected_pages_count_(0),
      should_print_backgrounds_(params.should_print_backgrounds),
      should_print_selection_only_(params.selection_only),
      is_printing_started_(false),
      weak_ptr_factory_(this) {
  PrintMsg_Print_Params print_params = params;
  if (!should_print_selection_only_ ||
      !PrintingNodeOrPdfFrame(frame, node_to_print_)) {
    bool fit_to_page =
        ignore_css_margins && IsWebPrintScalingOptionFitToPage(print_params);
    ComputeWebKitPrintParamsInDesiredDpi(params, &web_print_params_);
    frame->PrintBegin(web_print_params_, node_to_print_);
    double scale_factor = 1.0f;
    if (print_params.scale_factor >= PrintRenderFrameHelper::kEpsilon)
      scale_factor = print_params.scale_factor;
    print_params = CalculatePrintParamsForCss(
        frame, 0, print_params, ignore_css_margins, fit_to_page, &scale_factor);
    frame->PrintEnd();
  }
  ComputeWebKitPrintParamsInDesiredDpi(print_params, &web_print_params_);
}

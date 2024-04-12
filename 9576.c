void PrintRenderFrameHelper::ComputePageLayoutInPointsForCss(
    blink::WebLocalFrame* frame,
    int page_index,
    const PrintMsg_Print_Params& page_params,
    bool ignore_css_margins,
    double* scale_factor,
    PageSizeMargins* page_layout_in_points) {
  double input_scale_factor = *scale_factor;
  PrintMsg_Print_Params params = CalculatePrintParamsForCss(
      frame, page_index, page_params, ignore_css_margins,
      IsWebPrintScalingOptionFitToPage(page_params), scale_factor);
  CalculatePageLayoutFromPrintParams(params, input_scale_factor,
                                     page_layout_in_points);
}

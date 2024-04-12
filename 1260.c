bool PrintWebViewHelper::InitPrintSettings(bool fit_to_paper_size) {
  PrintMsg_PrintPages_Params settings;
  Send(new PrintHostMsg_GetDefaultPrintSettings(routing_id(),
                                                &settings.params));
  bool result = true;
  if (!PrintMsg_Print_Params_IsValid(settings.params))
    result = false;

  ignore_css_margins_ = false;
  settings.pages.clear();

  settings.params.print_scaling_option = blink::WebPrintScalingOptionSourceSize;
  if (fit_to_paper_size) {
    settings.params.print_scaling_option =
        blink::WebPrintScalingOptionFitToPrintableArea;
  }

  SetPrintPagesParams(settings);
  return result;
}

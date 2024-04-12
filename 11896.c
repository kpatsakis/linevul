void ComputeWebKitPrintParamsInDesiredDpi(
    const PrintMsg_Print_Params& print_params,
    WebKit::WebPrintParams* webkit_print_params) {
  int dpi = GetDPI(&print_params);
  webkit_print_params->printerDPI = dpi;
  webkit_print_params->printScalingOption = print_params.print_scaling_option;

  using printing::ConvertUnit;
  webkit_print_params->printContentArea.width =
      ConvertUnit(print_params.content_size.width(), dpi,
                  print_params.desired_dpi);
  webkit_print_params->printContentArea.height =
      ConvertUnit(print_params.content_size.height(), dpi,
                  print_params.desired_dpi);

  webkit_print_params->printableArea.x =
      ConvertUnit(print_params.printable_area.x(), dpi,
                  print_params.desired_dpi);
  webkit_print_params->printableArea.y =
      ConvertUnit(print_params.printable_area.y(), dpi,
                  print_params.desired_dpi);
  webkit_print_params->printableArea.width =
      ConvertUnit(print_params.printable_area.width(), dpi,
                  print_params.desired_dpi);
  webkit_print_params->printableArea.height =
      ConvertUnit(print_params.printable_area.height(),
                  dpi, print_params.desired_dpi);

  webkit_print_params->paperSize.width =
      ConvertUnit(print_params.page_size.width(), dpi,
                  print_params.desired_dpi);
  webkit_print_params->paperSize.height =
      ConvertUnit(print_params.page_size.height(), dpi,
                  print_params.desired_dpi);
}

bool PDFShouldDisableScaling(blink::WebLocalFrame* frame,
                             const blink::WebNode& node,
                             const PrintMsg_Print_Params& params,
                             bool ignore_page_size) {
  const bool kDefaultPDFShouldDisableScalingSetting = true;
  blink::WebPrintPresetOptions preset_options;
  if (!frame->GetPrintPresetOptionsForPlugin(node, &preset_options))
    return kDefaultPDFShouldDisableScalingSetting;
  return PDFShouldDisableScalingBasedOnPreset(preset_options, params,
                                              ignore_page_size);
}

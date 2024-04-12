MarginType GetMarginsForPdf(blink::WebLocalFrame* frame,
                            const blink::WebNode& node,
                            const PrintMsg_Print_Params& params) {
  return PDFShouldDisableScaling(frame, node, params, false)
             ? NO_MARGINS
             : PRINTABLE_AREA_MARGINS;
}

void PrintRenderFrameHelper::PrintPreviewContext::CalculateIsModifiable() {
  is_modifiable_ = !PrintingNodeOrPdfFrame(source_frame(), source_node_);
}

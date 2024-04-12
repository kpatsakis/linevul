void PDFiumEngine::Form_Print(IPDF_JSPLATFORM* param,
                              FPDF_BOOL ui,
                              int start,
                              int end,
                              FPDF_BOOL silent,
                              FPDF_BOOL shrink_to_fit,
                              FPDF_BOOL print_as_image,
                              FPDF_BOOL reverse,
                              FPDF_BOOL annotations) {
  PDFiumEngine* engine = static_cast<PDFiumEngine*>(param);
  engine->client_->Print();
}

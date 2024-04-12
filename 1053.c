int PDFiumEngine::Form_Response(IPDF_JSPLATFORM* param,
                                FPDF_WIDESTRING question,
                                FPDF_WIDESTRING title,
                                FPDF_WIDESTRING default_response,
                                FPDF_WIDESTRING label,
                                FPDF_BOOL password,
                                void* response,
                                int length) {
  std::string question_str = base::UTF16ToUTF8(
      reinterpret_cast<const base::char16*>(question));
  std::string default_str = base::UTF16ToUTF8(
      reinterpret_cast<const base::char16*>(default_response));

  PDFiumEngine* engine = static_cast<PDFiumEngine*>(param);
  std::string rv = engine->client_->Prompt(question_str, default_str);
  base::string16 rv_16 = base::UTF8ToUTF16(rv);
  int rv_bytes = rv_16.size() * sizeof(base::char16);
  if (response) {
    int bytes_to_copy = rv_bytes < length ? rv_bytes : length;
    memcpy(response, rv_16.c_str(), bytes_to_copy);
  }
  return rv_bytes;
}

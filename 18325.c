void PDFiumEngine::Form_EmailTo(FPDF_FORMFILLINFO* param,
                                FPDF_FILEHANDLER* file_handler,
                                FPDF_WIDESTRING to,
                                FPDF_WIDESTRING subject,
                                FPDF_WIDESTRING cc,
                                FPDF_WIDESTRING bcc,
                                FPDF_WIDESTRING message) {
  std::string to_str = WideStringToString(to);
  std::string subject_str = WideStringToString(subject);
  std::string cc_str = WideStringToString(cc);
  std::string bcc_str = WideStringToString(bcc);
  std::string message_str = WideStringToString(message);

  PDFiumEngine* engine = static_cast<PDFiumEngine*>(param);
  engine->client_->Email(to_str, cc_str, bcc_str, subject_str, message_str);
}

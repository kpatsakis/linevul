void MockPrinter::GetDefaultPrintSettings(PrintMsg_Print_Params* params) {
  EXPECT_EQ(-1, document_cookie_);

  document_cookie_ = CreateDocumentCookie();
  params->Reset();
  SetPrintParams(params);
}

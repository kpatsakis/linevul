void PrintPreviewMessageHandler::OnInvalidPrinterSettings(int document_cookie) {
  StopWorker(document_cookie);
  PrintPreviewUI* print_preview_ui = GetPrintPreviewUI();
  if (!print_preview_ui)
    return;
  print_preview_ui->OnInvalidPrinterSettings();
}

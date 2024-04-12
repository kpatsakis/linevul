void PrintPreviewHandler::HandleManagePrinters(const ListValue* /*args*/) {
  ++manage_printers_dialog_request_count_;
  printing::PrinterManagerDialog::ShowPrinterManagerDialog();
}

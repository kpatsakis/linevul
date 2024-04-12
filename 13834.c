PrintPreviewUI* PrintPreviewMessageHandler::GetPrintPreviewUI() {
  WebContents* dialog = GetPrintPreviewDialog();
  if (!dialog || !dialog->GetWebUI())
    return nullptr;
  return static_cast<PrintPreviewUI*>(dialog->GetWebUI()->GetController());
}

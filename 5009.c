void PrintPreviewDialogController::RemoveInitiator(
    WebContents* initiator) {
  WebContents* preview_dialog = GetPrintPreviewForContents(initiator);
  DCHECK(preview_dialog);
  preview_dialog_map_[preview_dialog] = nullptr;
  RemoveObservers(initiator);

  PrintViewManager::FromWebContents(initiator)->PrintPreviewDone();

  if (content::WebUI* web_ui = preview_dialog->GetWebUI()) {
    PrintPreviewUI* print_preview_ui =
        static_cast<PrintPreviewUI*>(web_ui->GetController());
    if (print_preview_ui)
      print_preview_ui->OnInitiatorClosed();
  }
}

void PrintPreviewHandler::HandleShowSystemDialog(const ListValue* /*args*/) {
  ReportStats();
  ReportUserActionHistogram(FALLBACK_TO_ADVANCED_SETTINGS_DIALOG);

  TabContents* initiator_tab = GetInitiatorTab();
  if (!initiator_tab)
    return;

  printing::PrintViewManager* manager = initiator_tab->print_view_manager();
  manager->set_observer(this);
  manager->PrintForSystemDialogNow();

  PrintPreviewUI* print_preview_ui = static_cast<PrintPreviewUI*>(
      web_ui()->GetController());
  print_preview_ui->OnCancelPendingPreviewRequest();
}

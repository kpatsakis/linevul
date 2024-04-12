void PrintPreviewUI::OnFileSelectionCancelled() {
  web_ui()->CallJavascriptFunction("fileSelectionCancelled");
 }
